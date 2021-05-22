#include "RapidJsonHelper.h"

//////////////////////////////////////////////////////////////////////////
// jsonファイルのオープン 
// in    : inFileName : オープンしたいjsonファイルパス
// inout : inoutDoc   : rapidjson オブジェクト
// オープンできた時は trueを返し、inoutDocに　rapidjsonDocumentを参照できる
//////////////////////////////////////////////////////////////////////////
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// jsonファイル開けるか？
	std::ifstream file(_inFileName);
	if (!file.is_open())
	{
		return false;
	}

	// filestreamにファイル文字列取り込む
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// ファイル文字列をJSon文字列に変換
	rapidjson::StringStream jsonStr(contents.c_str());
	// ファイルストリーム閉じる
	file.close();

	// 解析オブジェクト作成
	_inputDocument.ParseStream(jsonStr);

	// JSonObjectとして読めたか？
	if (!_inputDocument.IsObject())
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Doc内にそのメンバーは存在するか？
// in : inDoc      rapidjson Document
//    : memberName メンバー名
// 戻り値　Document内に memberNameが存在したときのみtrueを返す。
///////////////////////////////////////////////////////////////////////////////
bool IsExistMember(const rapidjson::Document& _inDocument, const char* _memberName)
{
	rapidjson::Value::ConstMemberIterator iter;
	iter = _inDocument.FindMember(_memberName);

	if (iter == _inDocument.MemberEnd())
	{
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// そのメンバーが存在し、かつ値が一致するか？
// in    :  inDoc       rapidjsonドキュメント
//          memberName  調べたいメンバー名
//          matchValue   調べたいメンバー名にマッチする値
// 戻り値 : memberNameに対応する値がmatchValueだったときのみtrueを返す 
/////////////////////////////////////////////////////////////////////////////////
bool IsExistMemberAndValue(const rapidjson::Document& _inDocument, const char* _menberName, const char* _matchValue)
{
	if (!IsExistMember(_inDocument, _menberName))
	{
		return false;
	}

	std::string findValueString;
	findValueString = std::string(_matchValue);

	if (findValueString != _inDocument[_menberName].GetString())
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
// Doc中に memberNameという名前の配列はあるか？
//////////////////////////////////////////////////////////////////////////
bool IsExistArrayName(const rapidjson::Document& _inDocument, const char* _menberName)
{
	rapidjson::Value::ConstMemberIterator iter;
	iter = _inDocument.FindMember(_menberName);
	if (iter == _inDocument.MemberEnd())
	{
		return false;
	}
	return _inDocument[_menberName].IsArray();
}

// JSON値を内容がintでも強制的にfloat 値として取得
float ForceGetFloat(const rapidjson::Value& val)
{
	std::string tmp;
	tmp = val.GetString();

	return static_cast<float>(atof(tmp.c_str()));
}

#include "RapidJsonHelper.h"

//////////////////////////////////////////////////////////////////////////
// json�t�@�C���̃I�[�v�� 
// in    : inFileName : �I�[�v��������json�t�@�C���p�X
// inout : inoutDoc   : rapidjson �I�u�W�F�N�g
// �I�[�v���ł������� true��Ԃ��AinoutDoc�Ɂ@rapidjsonDocument���Q�Ƃł���
//////////////////////////////////////////////////////////////////////////
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// json�t�@�C���J���邩�H
	std::ifstream file(_inFileName);
	if (!file.is_open())
	{
		return false;
	}

	// filestream�Ƀt�@�C���������荞��
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// �t�@�C���������JSon������ɕϊ�
	rapidjson::StringStream jsonStr(contents.c_str());
	// �t�@�C���X�g���[������
	file.close();

	// ��̓I�u�W�F�N�g�쐬
	_inputDocument.ParseStream(jsonStr);

	// JSonObject�Ƃ��ēǂ߂����H
	if (!_inputDocument.IsObject())
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Doc���ɂ��̃����o�[�͑��݂��邩�H
// in : inDoc      rapidjson Document
//    : memberName �����o�[��
// �߂�l�@Document���� memberName�����݂����Ƃ��̂�true��Ԃ��B
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
// ���̃����o�[�����݂��A���l����v���邩�H
// in    :  inDoc       rapidjson�h�L�������g
//          memberName  ���ׂ��������o�[��
//          matchValue   ���ׂ��������o�[���Ƀ}�b�`����l
// �߂�l : memberName�ɑΉ�����l��matchValue�������Ƃ��̂�true��Ԃ� 
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
// Doc���� memberName�Ƃ������O�̔z��͂��邩�H
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

// JSON�l����e��int�ł������I��float �l�Ƃ��Ď擾
float ForceGetFloat(const rapidjson::Value& val)
{
	std::string tmp;
	tmp = val.GetString();

	return static_cast<float>(atof(tmp.c_str()));
}

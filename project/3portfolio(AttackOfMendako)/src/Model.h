#pragma once

class Model
{
public:
	Model();
	~Model();

	// ���f���̓ǂݍ���
	void load( const  char * fileName_);
	// ���f���̍폜
	void exit();
	// ���f���̍��W�ݒ�
	void setPos(VECTOR pos_);
	// ���f���̉�]
	void setRota(VECTOR rota_);

	// ���f���̔{���ύX
	void setScale(VECTOR scale_);

	void init();
	// ���f���̕`��
	void draw();

	// ���f���n���h���擾
	int handle() { return _handle; }


private:
	// ���f���̃n���h��
	int _handle;
	// �t�@�C����
	const  char * _fileName;


};

#pragma once

class Game
{
public:
	Game() {};
	virtual~Game() {};

	void Init(void);		//	����������
	void Exit(void);		//	�I������
	void Update(void);	    //	�X�V����
	void Render(void);	    //	�`�揈��


private:

	// �V�[���}�l�[�W���[�̃C���X�^���X
	class SceneManager * _sMngIns;
	


};




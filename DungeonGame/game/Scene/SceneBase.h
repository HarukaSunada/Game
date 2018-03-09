#pragma once
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();
	/*!
	* @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	*/
	virtual void Init()
	{

	}
	/*!
	* @brief	�X�V�B
	*/
	virtual void Update() = 0;
	/*!
	* @brief	�`��B
	*/
	virtual void Render();

	virtual void PostRender();

	//�V�[�����I��������ǂ���
	bool isSceneEnd()
	{
		return sceneEnd;
	}

protected:
	bool			sceneEnd = false;	//�V�[���I���t���O
};

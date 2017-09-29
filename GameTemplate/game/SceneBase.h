#pragma once
class SceneBase
{
public:
	SceneBase();
	~SceneBase();
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
	virtual void Render() = 0;
};


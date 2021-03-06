#pragma once
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();
	/*!
	* @brief	ゲームが起動してから一度だけ呼ばれる関数。
	*/
	virtual void Init()
	{

	}
	/*!
	* @brief	更新。
	*/
	virtual void Update() = 0;
	/*!
	* @brief	描画。
	*/
	virtual void Render();

	virtual void PostRender();

	//シーンが終わったかどうか
	bool isSceneEnd()
	{
		return sceneEnd;
	}

protected:
	bool			sceneEnd = false;	//シーン終了フラグ
};


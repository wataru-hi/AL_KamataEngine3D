#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

class Player
{
public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection_);

private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	uint32_t textureHandle_ = 0;
	Input* input_ = nullptr;

	//キャラクターの移動速さ
	const float kCaracterSpeed = 0.2f;
	
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;
};
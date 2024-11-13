#include "Player.h"
#include <cassert>
#include "MathUtilityForText.h"
#include <ImGuiManager.h>


void Player::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();

	input_ = Input::GetInstance();
}

void Player::Update()
{
	Vector3 move = {0,0,0};

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCaracterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)){
		move.x += kCaracterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCaracterSpeed;
	}
	else if (input_->PushKey(DIK_UP)){
		move.y += kCaracterSpeed;
	}
	
	Rotate();

	worldTransform_.translation_ += move;

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	float PlayerTranslate[3] = {worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z};

	ImGui::Begin("data");
	ImGui::DragFloat3("PlayerPos", PlayerTranslate, 0.1f, 1.0f);
	ImGui::End();

	worldTransform_.translation_.x = PlayerTranslate[0];
	worldTransform_.translation_.y = PlayerTranslate[1];
	worldTransform_.translation_.z = PlayerTranslate[2];

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	Attack();

	//if(Bullet_){Bullet_->Update();}

	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//if(Bullet_){Bullet_->Droaw(viewProjection_);}
}

void Player::Rotate()
{
	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_A))
	{
		worldTransform_.rotation_.y += kRotSpeed;
	}
	else if (input_->PushKey(DIK_D))
	{
		worldTransform_.rotation_.y -= kRotSpeed;
	}

}

void Player::Attack()
{
	//if (input_->PushKey(DIK_SPACE)) {
	//	PlayerBulllet* newBullet = new PlayerBulllet();
	//	newBullet->Initialize(model_, worldTransform_.translation_);

	//	Bullet_ = newBullet;
	//}
}

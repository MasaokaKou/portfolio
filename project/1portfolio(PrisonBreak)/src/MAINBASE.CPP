#include "MainBase.h"

MainBase::MainBase()
{
}

MainBase::~MainBase()
{
}

void MainBase::Update() {

}
void MainBase::Render() {

}
float MainBase::GetX() {
	return x;
}
float MainBase::GetY() {
	return y;
}
float MainBase::GetV() {
	return v;
}
float MainBase::GetSize() {
	return size;
}
int MainBase::GetDir() {
	return dir;
}

void MainBase::SetX(float num) {
	 x=num;
}
void MainBase::SetY(float num) {
	 y=num;
}
void MainBase::SetDir(int num) {
	 dir=num;
}
void MainBase::SetSize(float num) {
	 size=num;
}
void MainBase::SetV(float num)
{
	 v=num;
}

#pragma once
#include <vector>
#include <string>
#include <cassert>
#include <DxLib.h>

/// <summary>
/// 文字列ユーティリティ
/// </summary>
namespace StringUtil
{
	/// <summary>
	/// 文字列を分割する
	/// </summary>
	/// <param name="str">分割する文字列</param>
	/// <param name="delim">区切り文字</param>
	/// <returns>分割された文字列の配列</returns>
	std::vector<std::string> Split(std::string& str, char delimiter);

	/// <summary>
	/// 指定した座標を中心に文字列を描画する
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="x">X軸</param>
	/// <param name="y">Y軸</param>
	/// <param name="color">色</param>
	/// <param name="str">文字列</param>
	/// <param name="fontHandle">フォントハンドル</param>
	void DrawStringCenter(int x, int y, unsigned int color, std::string str, int fontHandle);
}
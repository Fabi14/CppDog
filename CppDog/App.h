#pragma once
#include "olcPixelGameEngine.h"
#include "Level.h"


namespace
{
	const olc::vf2d dogSize{ 100,100 };
	const olc::vf2d startPos{ dogSize.x * 3,dogSize.y * 7 };
	std::vector< olc::vf2d> vecfinalPos
	{
		{ dogSize.x * 7,dogSize.y * 9 },
		{ dogSize.x * 11,dogSize.y * 6 },
		{ dogSize.x * 2,dogSize.y * 4 }
	};
}

class App : public olc::PixelGameEngine
{
public:
	App()
	{
		// Name your application
		sAppName = "CppDog";
	}

public:
	bool OnUserCreate() override
	{
		{
			olc::Renderable h01;
			h01.Load("./assets/Level_01.png");
			m_vecHelpImages.emplace_back(std::move(h01));
		}
		{
			olc::Renderable h01;
			h01.Load("./assets/Level_02.png");
			m_vecHelpImages.emplace_back(std::move(h01));
		}
		{
			olc::Renderable h01;
			h01.Load("./assets/Level_03.png");
			m_vecHelpImages.emplace_back(std::move(h01));
		}
		return true;
	}
	void drawBackground()
	{
		for (float x = 0; x < ScreenWidth(); x += dogSize.x*2)
		{
			for (float y = 0; y < ScreenHeight(); y += dogSize.y*2)
			{
				FillRectDecal({x,y}, dogSize, olc::GREY);
			}
		}
		for (float x = dogSize.x; x < ScreenWidth(); x += dogSize.x * 2)
		{
			for (float y = dogSize.y; y < ScreenHeight(); y += dogSize.y * 2)
			{
				FillRectDecal({ x,y }, dogSize, olc::GREY);
			}
		}
		
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::WHITE);
		drawBackground();
		m_time += fElapsedTime;

		constexpr float timeFactor = 1.5f;

		auto playTime = m_time * timeFactor;

		if (playTime < m_vecDirections.size())
		{
			auto currentDir = m_vecDirections[static_cast<size_t>(playTime)];

			switch (currentDir)
			{
			case Direction::left:
				m_pos.x -= dogSize.x * fElapsedTime * timeFactor;
				break;
			case Direction::right:
				m_pos.x += dogSize.x * fElapsedTime * timeFactor;
				break;
			case Direction::up:
				m_pos.y -= dogSize.y * fElapsedTime * timeFactor;
				break;
			case Direction::down:
				m_pos.y += dogSize.y * fElapsedTime * timeFactor;
				break;
			default:
				break;
			}

		}


		olc::vf2d finalPos = vecfinalPos[m_levelCount];

		FillRectDecal(finalPos, dogSize, olc::GREEN);


		FillRectDecal(m_pos, dogSize, olc::RED);

		for (auto wall : m_wallPos)
		{
			FillRectDecal(wall, dogSize, olc::BLACK);
		}

		if (std::abs(m_pos.x - finalPos.x) < 5 &&
			std::abs(m_pos.y - finalPos.y) < 5)
		{
			if (m_levelCount < vecfinalPos.size() - 1)
			{
				m_levelCount++;
				switch (m_levelCount)
				{
				case 1:
					m_wallPos.push_back({ dogSize.x * 7,dogSize.y * 6 });
					m_wallPos.push_back({ dogSize.x * 8,dogSize.y * 6 });
					m_wallPos.push_back({ dogSize.x * 6,dogSize.y * 6 });
					m_wallPos.push_back({ dogSize.x * 9,dogSize.y * 9 });
					m_wallPos.push_back({ dogSize.x * 9,dogSize.y * 8 });
					m_wallPos.push_back({ dogSize.x * 10,dogSize.y * 6 });
					m_wallPos.push_back({ dogSize.x * 10,dogSize.y * 7 });
					break;
				case 2:
					m_wallPos.push_back({ dogSize.x * 6,dogSize.y * 5 });
					m_wallPos.push_back({ dogSize.x * 6,dogSize.y * 4 });
					m_wallPos.push_back({ dogSize.x * 6,dogSize.y * 3 });
					m_wallPos.push_back({ dogSize.x * 6,dogSize.y * 2 });
					break;
				default:
					break;
				}

			}
			else
			{
				DrawStringDecal({ ScreenWidth() * 0.5f - 400.f,ScreenHeight() * 0.5f - 100.f }, "Gewonnen!", olc::RED, { 10.f,10.f });
			}
		}




		if (GetKey(olc::SPACE).bPressed)
		{
			m_time = 0.f;
			m_pos = startPos;
			m_levelCount = 0;
		}
		if (GetKey(olc::H).bPressed)
		{
			m_helpPressed = !m_helpPressed;
		}
		if (m_helpPressed)
		{
			DrawDecal({ ScreenWidth() * 0.5f - 0.5f * m_vecHelpImages[m_levelCount].Sprite()->Size().x,
				ScreenHeight() * 0.5f - 0.5f * m_vecHelpImages[m_levelCount].Sprite()->Size().y },
				m_vecHelpImages[m_levelCount].Decal());
		}
		if (GetKey(olc::ESCAPE).bPressed)
		{
			return false;
		}
		return true;
	}

	void runDog(Direction direction)
	{
		m_vecDirections.push_back(direction);
	}

private:
	float m_time{};
	olc::vf2d m_pos{ startPos };
	std::vector<Direction> m_vecDirections;
	int m_levelCount{ 0 };
	bool m_helpPressed{ false };

	std::vector<olc::Renderable> m_vecHelpImages;
	std::vector<olc::vf2d> m_wallPos;
};
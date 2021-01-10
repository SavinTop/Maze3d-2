#include "coloredMapGenerator.hpp"


void ColoredMapGenerator::generateMap(MazeBuilder& mb) 
{
    const int wallLength = 4;

    int width;
	int height;
	bool **v_walls;
	bool **h_walls;
	mb.getWalls(v_walls, h_walls, width, height);

    int m_width = (width-1)*(wallLength)+1;
    int m_height = (height-1)*(wallLength)+1;

    img.setSize(m_width,m_height);
    for (int y = 0; y < m_height; y++)
		for (int x = 0; x < m_width; x++)
            img.setPixel(x,y,Color::rgba(25,25,25,255));


    for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
            img.setPixel(x*wallLength,y*wallLength,Color::rgba(255,255,255,255));
			if(h_walls[width-x-1][height-y-1])
            {
                for(int c=1;c<wallLength;c++)
                    img.setPixel(x*wallLength-c,y*wallLength,Color::rgba(255,255,255,255));
            }
            if(v_walls[width-x-1][height-y-1])
            {
                for(int c=1;c<wallLength;c++)
                    img.setPixel(x*wallLength,y*wallLength-c,Color::rgba(255,255,255,255));
            }
		}
	}

    img.setPixel((width-1)*wallLength-2,(height-1)*wallLength-2,Color::rgba(255,255,0,255));

}

#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    //probably width
    int w=32;

    
    int grid[12][12];
    int sgrid[12][12]; //for showing


    //texture 
    Texture t;
    t.loadFromFile("images/minesweeper/tiles.jpg");
    
    
    Sprite s(t);

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        // every square isn't open 
        sgrid[i][j]=10;

        //putting mines, default chanse that there is mine = 25%
        if (rand()%5==0)  grid[i][j]=9;
        //else 75% is for empty square
        else grid[i][j]=0;
      }

    //this for loop is used for defining how many mines near this square
    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (grid[i][j]==9) continue;
        if (grid[i+1][j]==9) n++;
        if (grid[i][j+1]==9) n++;
        if (grid[i-1][j]==9) n++;
        if (grid[i][j-1]==9) n++;
        if (grid[i+1][j+1]==9) n++;
        if (grid[i-1][j-1]==9) n++;
        if (grid[i-1][j+1]==9) n++;
        if (grid[i+1][j-1]==9) n++;
        grid[i][j]=n;
      }

    //while player is playing 
    while (app.isOpen())
    {
        // mouse position
        Vector2i pos = Mouse::getPosition(app);
        
        //current position of mouse
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;
        while (app.pollEvent(e))
        {   
            //if player decide to close the game
            if (e.type == Event::Closed)
                app.close();


            if (e.type == Event::MouseButtonPressed)
                //when player left click on square depends on what does the square actually contain it's changing on mine/empty square
              if (e.key.code == Mouse::Left) sgrid[x][y]=grid[x][y];
                //if player right click on square the flag image appears on this square
              else if (e.key.code == Mouse::Right) sgrid[x][y]=11;
        }


        //Background color
        app.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
           if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
           s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));
           s.setPosition(i*w, j*w);
           app.draw(s);
          }

        app.display();
    }

    return 0;
}

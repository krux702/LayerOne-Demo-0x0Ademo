int y_fadein = 12;
int x_fadein = 76;
int lastStoryFrame = 200;

void initExample2(uint8_t double_buffer) {
  // scene init code here

  // config_graphics args:
  // MODE_640x480 - timing definition from vga.c
  // 640, 480 - canvas horizontal and vertical resolution
  // 1 - Color depth (bits per pixel)
  // 0 - x offset, display vs canvas offset
  // 0 - y offset, display vs canvas offset
  // double_buffer - double buffer support as passed by scene manager
  //    config_graphics(MODE_640x480, 640UL, 480UL, 1, 0, 0, double_buffer);
  //    config_graphics(MODE_320x480, 320UL, 480UL, 2, 0, 0, 0);
  config_graphics(MODE_160x480, 160UL, 480UL, 4, 0, 0, double_buffer);

  // 16 bit color - 5 6 5
    
  // grayscale
  set_clut(0, 0x0000);
  set_clut(1, 0x52aa);
  set_clut(2, 0xA554);
  set_clut(3, 0xffff);

  // red
  set_clut(4, 0x4000);
  set_clut(5, 0x8000);
  set_clut(6, 0xb800);
  set_clut(7, 0xf800);

  // green
  set_clut(8, 0x0170);
  set_clut(9, 0x03c0);
  set_clut(10, 0x05a0);
  set_clut(11, 0x0770);

  // blue
  set_clut(12, 0x0008);
  set_clut(13, 0x0010);
  set_clut(14, 0x0017);
  set_clut(15, 0x001f);
   
  // set our starting point
   
  // enable sound timer
  // http://wry.me/bytebeat/
  track=TRACK_INTRO;
  _T1IE=1;
}

void drawExample2()
{
  // frame draw code here
      
  int l1_x = 0;
  int l1_y = 0;
  if(storyFrame > lastStoryFrame && y_fadein < ((VER_RES>>1)-12)) 
  {
    y_fadein = y_fadein + 12;
    lastStoryFrame = storyFrame + 10;
  }
  
  if(storyFrame > 300)
  {
    if(storyFrame > 550 && x_fadein > 0)
    {
      x_fadein = x_fadein - 4;
    }

    if(storyFrame < 600)
    {
      l1_x = 25 * (fcos(storyFrame<<3));
      l1_y = 50 * (fsin(storyFrame<<3));
    }
    else
    {
      if(l1_x < (HOR_RES>>1))
      {
        l1_x++;
      }
      if(l1_x > (HOR_RES>>1))
      {
        l1_x--;
      }
      if(l1_y < (VER_RES>>1))
      {
        l1_y++;
      }
      if(l1_y > (VER_RES>>1))
      {
        l1_y--;
      }
    }
  }
 
  draw_plasma((HOR_RES>>1) - x_fadein, (HOR_RES>>1) + x_fadein, (VER_RES>>1) - y_fadein, (VER_RES>>1) + y_fadein);

  draw_layerone((HOR_RES>>1)+l1_x,(VER_RES>>1)+l1_y);
}
/*
static unsigned int sqrtI( unsigned long sqrtArg )
{
  unsigned int answer, x;
  unsigned long temp;

  if ( sqrtArg == 0 ) return 0; // undefined result
  if ( sqrtArg == 1 ) return 1; // identity
  answer = 0;                     // integer square root
  for( x=0x8000; x>0; x=x>>1 )
  {                                 // 16 bit shift
    answer |= x;             // possible bit in root
    temp = __builtin_muluu(answer, answer); // fast unsigned multiply
    if (temp == sqrtArg) break; // exact, found it
    if (temp > sqrtArg) answer ^= x; // too large, reverse bit
  }
  return answer; // approximate root
}
*/
void draw_plasma(int x_start, int x_end, int y_start, int y_end)
{
  int x,y,color;
  // for(y = y_start; y < y_end; y = y + 12)
  for(y = 12; y < (VER_RES - 12); y = y + 12)
  {
    for(x = 4; x < (HOR_RES - 4); x = x + 4)
    {
      color = (int)( 
        fsin(x + storyFrame) +
        (2 * fsin(y + storyFrame)) +
        (4 * fsin(((x + storyFrame) + (y + storyFrame>>2)))) 
      );

      if(y <= y_start || y >= y_end)
      {
        color = 0;
      }
      if(x <= x_start || x >= x_end)
      {
        color = 0;
      }
      safe_color(color);
      fast_draw(x, y, 4, 12);
   }
  }
}

void draw_layerone(int x, int y)
{
  safe_color(1);
  safe_draw(x - 20, y - 84, 16, 126);
  safe_draw(x - 4, y, 8, 42);
    
  safe_color(3);
  safe_draw(x + 4, y - 42, 16, 126);
  safe_draw(x - 4, y - 42, 8, 42);

  safe_color(0);
  safe_draw(x - 21, y - 87, 1, 129);
  safe_draw(x - 20, y - 87, 16, 3);
  safe_draw(x - 4, y - 87, 1, 45);
  safe_draw(x - 4, y - 42, 24, 3);
  safe_draw(x + 20, y - 42, 1, 129);
  safe_draw(x + 4, y + 84, 16, 3);
  safe_draw(x + 3, y + 42, 1, 45);
  safe_draw(x - 21, y + 42, 24, 3);
}
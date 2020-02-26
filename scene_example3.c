int scroll_char = 0;
int scroll_offset = 0;

void initExample3(uint8_t double_buffer) {
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

void drawExample3()
{
  // frame draw code here
  int l1_x = 0;
  int l1_y = 0;  
  int r_offset = 0;    
  int g_offset = 0;    
  int b_offset = 0;
  int bar_order = 0;

  char scroller[] = "           ... and thus the end of this little demo ... greets go out to psychoholics (fuck yeah!), pinguino, datagram, charliex, syn shop, and 23b ... oh and \"rm dkuvieebrt rn oroatnmeoiy le\"         ";
  char scroll_buff[] = "        ";

  l1_x = 25 * (fcos(storyFrame<<3));
  l1_y = 50 * (fsin(storyFrame<<3));  
  draw_layerone((HOR_RES>>1)+l1_x,(VER_RES>>1)+l1_y);
  
  if(scroll_offset == 0)
  {
    scroll_char++;
    if(scroller[scroll_char+10] == 0)
    {
      scroll_char = 0;
    }
  }

  int n;
  for(n=0 ; n<7 ; n++)
  { 
    scroll_buff[n] = scroller[n+scroll_char];
  }

  font_color(3,0);
  chr_print(scroll_buff, 19 - scroll_offset, 400);

  safe_color(0);
  safe_draw(0,400,16,48);
  safe_draw(143,400,16,48);
  
  scroll_offset = scroll_offset + 2;
  if(scroll_offset > 19)
  {
    scroll_offset = 0;
  }
  
  int x,y;
  // bouncy sin wave scroller path
  for(x = 1; x < HOR_RES -1; x++)
  {
    y = (VER_RES >> 1) + (100 * fsin((x + HOR_RES + storyFrame << 3) >> 4)) + (70 * fsin((x + (storyFrame << 5) >> 3)));

    r_offset = (40 * fsin(x + storyFrame<<2));
    g_offset = (40 * fsin(x + 120 + storyFrame<<2));
    b_offset = (40 * fsin(x + 240 + storyFrame<<2));

    if(r_offset > 35)
    {
      bar_order = 0;
    }
    if(g_offset > 35)
    {
      bar_order = 1;
    }
    if(b_offset > 35)
    {
      bar_order = 2;
    }
      
    if(bar_order == 0)
    {
      draw_bar_segment(x,y+g_offset,8);
      draw_bar_segment(x,y+b_offset,12);
      draw_bar_segment(x,y+r_offset,4);
    }
    else if(bar_order == 1)
    {
      draw_bar_segment(x,y+b_offset,12);
      draw_bar_segment(x,y+r_offset,4);
      draw_bar_segment(x,y+g_offset,8);
    }
    else if(bar_order == 2)
    {
      draw_bar_segment(x,y+r_offset,4);
      draw_bar_segment(x,y+g_offset,8);
      draw_bar_segment(x,y+b_offset,12);
    }
  }
}

void draw_bar_segment(int x, int y, int color)
{
  // 0
  safe_color(0);
  fast_pdraw(x,y);

  // 1
  safe_color(color);
  y++;
  fast_pdraw(x,y);

  // 2
  color++;
  y++;
  safe_color(color);
  fast_pdraw(x,y);

  // 3
  color++;
  y++;
  safe_color(color);
  fast_pdraw(x,y);

  // 4
  color++;
  y++;
  safe_color(color);
  fast_pdraw(x,y);

  // 3
  color--;
  y++;
  safe_color(color);
  fast_pdraw(x,y);

  // 2
  color--;
  y++;
  safe_color(color);
  fast_pdraw(x,y);

  // 1
  color--;
  y++;
  safe_color(color);
  fast_pdraw(x,y);

  // 0
  safe_color(0);
  y++;
  safe_color(color);
  fast_pdraw(x,y);
}

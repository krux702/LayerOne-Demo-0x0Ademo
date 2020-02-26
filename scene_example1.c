int y1,y2,count_frames;

void initExample1(uint8_t double_buffer) {
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
  _T1IE=0;
  
  count_frames = 0;
  y2 = 42;
  y1 = VER_RES - 126 + 84;
}

void drawExample1()
{
  // frame draw code here
  int x;
  x = HOR_RES>>1;

  count_frames++;
  
  if(count_frames < 800)
  {
    font_color(14,0);
    chr_print("krux", 40, 30);
    if(count_frames > 100)
    {
      font_color(15,0);
      chr_print("presents", 0, 70);
    }
    if(count_frames > 600)
    {
      font_color(14,0);
      chr_print("0x0Ademo", 0, 360);
      _T1IE=1;
    }
  }
  if(count_frames > 200)
  {
    y1--;
    if(y1 < (VER_RES>>1) )
    {
      y1 = (VER_RES>>1);
      y2++;
    
      safe_color(3);
      safe_draw(x + 4, y2 - 42, 16, 126);
      safe_draw(x - 4, y2 - 42, 8, 42);
    }
    if(y2 > (VER_RES>>1) )
    {
      y2 = (VER_RES>>1);
    }

    safe_color(1);
    safe_draw(x - 20, y1 - 84, 16, 126);
    safe_draw(x - 4, y1, 8, 42);
  }
}

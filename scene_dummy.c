
void initDummy(uint8_t double_buffer)
{
    config_graphics(MODE_640x480, 640UL, 480UL, 1UL, 0UL, 0UL, double_buffer);
    hsyncFunction = &doNothing;
    vsyncFunction = &doNothing;
    _HMRGNIE = 0;
    //_VMRGNIE = 0;
    _GFX1IE = 0;
}

void initDummy320(uint8_t double_buffer)
{
    config_graphics(MODE_320x480, 320UL, 480UL, 1UL, 0UL, 0UL, double_buffer);
    hsyncFunction = &doNothing;
    vsyncFunction = &doNothing;
    _HMRGNIE = 0;
    //_VMRGNIE = 0;
    _GFX1IE = 0;
}

void initDummy160(uint8_t double_buffer)
{
    config_graphics(MODE_160x480, 160UL, 480UL, 1UL, 0UL, 0UL, double_buffer);
    hsyncFunction = &doNothing;
    vsyncFunction = &doNothing;
    _HMRGNIE = 0;
    //_VMRGNIE = 0;
    _GFX1IE = 0;
    set_clut(0, 0x0000);
    set_clut(1, 0x52aa);
}

void drawDummy(uint16_t storyFrame)
{
   safe_color(1);

   borderScreen();
}

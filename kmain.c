void main()
{
    char* video = (char*)0xb8000;
    *video = 'X';
    *(video + 2) = 'H';
}

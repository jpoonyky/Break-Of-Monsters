#ifndef __DISP_NUMBER_H__
#define	__DISP_NUMBER_H__


class C_DispNumber
{
private:
	struct tag_BitNum{
		char	num;
		int		x,	y;
		float	w, h;
	}*BitNum;
	const int	MAX_DIGIT;
	int			num, dispDigit;
	iex2DObj*	img;
	int			imgFontSize, imgDivide;
	int			fontSize;

public:
	C_DispNumber( int digit );
	~C_DispNumber(){
		if( BitNum  != NULL )		delete[]	BitNum;
		if( img		!= NULL )		delete		img;
	}
	bool	LoadImage( char* filename, int fontSize, int divide );
	void	SetFontSize( int size = -1 );
	bool	SetNumber( int n );
	int		GetNum()		{	return	num;		}
	void	Update(){};
	void	Render( int x, int y, DWORD color );
};

#endif // !__DISP_NUMBER_H__
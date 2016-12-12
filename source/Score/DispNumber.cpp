#include	"iextreme.h"
#include	"DispNumber.h"


C_DispNumber::C_DispNumber( int digit ) : MAX_DIGIT( digit ), num(0), dispDigit(0), img( NULL ), 
											  imgFontSize(0), fontSize( 0 )
{
	BitNum	= new tag_BitNum[ digit ];

	for( int i=0; i<digit; i++ )
	{
		BitNum[ i ].num	= BitNum[ i ].x		= BitNum[ i ].y	= 0;
		BitNum[ i ].w	= BitNum[ i ].h	= 0.0f;
	}
}


bool	C_DispNumber::LoadImage( char* filename, int fontSize, int divide )
{
	img			= new iex2DObj( filename );
	imgFontSize	= fontSize;
	imgDivide	= divide;
	SetFontSize();

	return		true;
}

void	C_DispNumber::SetFontSize( int size )
{
	fontSize	= size;
	if( size == -1 )	fontSize	= imgFontSize;
}

bool	C_DispNumber::SetNumber( int n )
{
	num			= n;
	dispDigit	= 0;				//	‰Šú‰»

	int	x = -fontSize;

	for( int i=0; i<MAX_DIGIT; i++){
		BitNum[ i ].num	= n % 10;
		BitNum[ i ].x	= x;
		BitNum[ i ].y	= 0;
		BitNum[ i ].w	= BitNum[ i ].h	= fontSize;

		n	/= 10;
		x	-= fontSize;
	}

	return	true;
}

void	C_DispNumber::Render( int x, int y, DWORD color )
{
	int	loop	= MAX_DIGIT;
	for( int i=0; i<loop; i++ ){
		img->Render( x+BitNum[i].x, y+BitNum[i].y, BitNum[i].w, BitNum[i].h, 
			(BitNum[i].num%imgDivide)*imgFontSize, (BitNum[i].num/imgDivide)*imgFontSize,
			imgFontSize, imgFontSize, RS_COPY, color );
	}
}

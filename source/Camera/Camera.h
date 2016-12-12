#ifndef _CAMERA_H_
#define _CAMERA_H_
//*********************************************************************
//		define��`
//*********************************************************************
#define	CAMERA_MIN_LENGTH	20.0f
#define	CAMERA_MAX_LENGTH	400.0f


class Camera : public iexView
{
private:
	Vector3	pos, target;
	Vector3 cameraUPvec;

	Vector3 angle;					//�R���g���[���pangle
	int mode;						//�f�o�b�N�p���[�h
	int cameramode;
	Camera();
	~Camera();

public:

	void Init(int mode);
	void MainCamera( const Vector3 &p , const Vector3 &f );
	void SubCamera(Vector3 t, Vector3 p);
	void TitleCamera(Vector3 t, Vector3 p);
	void Update(Vector3 t, Vector3 p);
	
	void Render();
	void MainRender();


	Vector3 getPos(){ return Pos; };
	Vector3 getTarget(){ return Target; };

	void SetMode(int mode){ this->cameramode = mode; }
	/*�@Singleton�@*/
	static Camera* getInstance()
	{
		static Camera instance;
		return &instance;
	}

};

#endif
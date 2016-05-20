#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include <cinder/gl/Texture.h>
#include "cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
    CameraPersp  camera; // ������
    Quatf sceneRotation; // ������� ������
    Vec3f eyePosition; // �������� ������
    float cameraDistance; // ���������� �� ������ �� ����
    Vec3f objectPosition;
	gl::Texture img;
	params::InterfaceGl cameraParams; // ���������������� ��������� ��� ������ � �������
  public:
    void setup() { // ��������� ��� ������� ����������
		img = loadImage( "image.png" );
        objectPosition =  Vec3f::zero();
        cameraDistance = 500; // �������� �������� �� ��������� �� ������ �� ����
        camera.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f ); // �������� ����������� ������

        cameraParams = params::InterfaceGl( "Camera Settings", Vec2i( 225, 200 ) ); // �������� ���� ���������� (��������, ������)
        cameraParams.addParam( "Scene Rotation", &sceneRotation ); // ���� ����� ��������� ��������� �����
        cameraParams.addParam( "Eye Distance", &cameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" ); // ���� ����� ��������� ����������� �� ���� ��� ������ �� ���� ���� ��� ������� (��������� � ���������� http://anttweakbar.sourceforge.net/doc/tools%3aanttweakbar%3avarparamsyntax)
    }

    void keyDown( KeyEvent event ) {
        if( event.getCode() == KeyEvent::KEY_UP) {
            objectPosition.y += 10;
        }
        if( event.getCode() == KeyEvent::KEY_DOWN) {
            objectPosition.y -= 10;
        }
        if( event.getCode() == KeyEvent::KEY_LEFT) {
            objectPosition.x -= 10;
        }
        if( event.getCode() == KeyEvent::KEY_RIGHT) {
            objectPosition.x += 10;
        }
    }

    void update() { // ���� ������ ���������� ������ ���������� ���������� � ����� � ������������ ������ �����. ��������� ������ ����
        eyePosition = Vec3f( 0.0f, 0.0f, cameraDistance ); // ����������������� �������� ��������� ������ �� ����� (x, y, ���������� �� ������ �� ����)
        camera.lookAt( eyePosition, Vec3f::zero(), Vec3f::yAxis() ); // ������� (������ �������, �� ��� ��� ���� ���������, ����� ������� ����)
        gl::setMatrices( camera ); // ���������� �������� ����������� � ��� ��� ���������� ��� (��������� ������)
        gl::rotate( sceneRotation ); // ��������� ������� ����� 
    }

    void draw() { // ���� ������ ���������� ������ ����������� ���������� � ����� � ������������ ������ �����. ��������� ������ ����
		gl::clear( Color( 0.0f, 0.0f, 0.0f ) );
		gl::draw(img, Vec2f(objectPosition.x ,objectPosition.y));
        cameraParams.draw(); // ���������� ���� ����������
    }
};

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
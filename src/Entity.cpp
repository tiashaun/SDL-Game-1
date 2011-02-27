#include "Entity.h"
#include <SDL/SDL_image.h>
#include <Box2D/Box2D.h>

Entity::Entity()
{
    m_iX = 50;
    m_iY = 0;
    m_iXVel = 0;
    m_iYVel = 0;

    m_iSpeed = 1;

    m_sCurrentAnimation = "Standing";
}

Entity::~Entity()
{
    SDL_FreeSurface( image );
}

void Entity::InitPhysics(b2World *physicsWorld) {
    m_b2BodyDef.type = b2_dynamicBody;
    m_b2BodyDef.position.Set(20.0f, 5.0f);
    m_b2BodyDef.angularDamping = 0.0f;
    m_b2BodyDef.fixedRotation = true;
    m_b2Body = physicsWorld->CreateBody(&m_b2BodyDef);

    m_b2DynamicBox.SetAsBox((30/2.0)*0.1f, (40/2.0)*0.1f);
    //m_b2DynamicBox.SetAsBox(32*0.1f, 40*0.1f);
    //m_b2DynamicBox.SetAsBox(1.0, 1.0);

    m_b2FixtureDef.shape = &m_b2DynamicBox;
    m_b2FixtureDef.density = 1.0f;
    m_b2FixtureDef.friction = 0.0f;
    //m_b2FixtureDef.restitution = 0.3;

    m_b2Body->CreateFixture(&m_b2FixtureDef);
}

void Entity::Init(std::string xmlFileName) {
    m_asAnimations.Init(xmlFileName);
    std::string imageFileName = m_asAnimations.GetImageFileName();

    int colorkeyR = m_asAnimations.GetColorKeyValue('r');
    int colorkeyG = m_asAnimations.GetColorKeyValue('g');
    int colorKeyB = m_asAnimations.GetColorKeyValue('b');

    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( imageFileName.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, colorkeyR, colorkeyG, colorKeyB ) );
        }
    } else {
        return;
    }

    //Return the optimized surface
    image = optimizedImage;
}

void Entity::ApplySurface(int iX, int iY, SDL_Surface* pDestination, SDL_Rect* clip = NULL) {
    SDL_Rect offset;

    offset.x = iX;
    offset.y = iY;

    SDL_BlitSurface(image, clip, pDestination, &offset);
}

void Entity::Draw(SDL_Surface* pDestination) {
    SDL_Rect currentClip = m_asAnimations.GetCurrentClip(m_sCurrentAnimation);

    ApplySurface(m_iX, m_iY, pDestination, &currentClip);
}

void Entity::Think(int iElapsedTime) {
    //get its new position
    b2Vec2 position = m_b2Body->GetPosition();

    m_iX = position.x * 10.0f;
    m_iY = -position.y * 10.0f;

    m_asAnimations.UpdateFrames( iElapsedTime, m_sCurrentAnimation );
}

void Entity::SetXVelocity(int iXVel) {
    m_iXVel = iXVel;
}

void Entity::SetYVelocity(int iYVel) {
    m_iYVel = iYVel;
}

void Entity::AddXVelocity(int iXVel) {
    m_iXVel += iXVel;
}

void Entity::AddYVelocity(int iYVel) {
    m_iYVel += iYVel;
}

int Entity::GetSpeed() {
    return m_iSpeed;
}

void Entity::SetAnimation(std::string sAnimationEnum) {
    m_sCurrentAnimation = sAnimationEnum;
}

b2Body* Entity::GetBody() {
    return m_b2Body;
}























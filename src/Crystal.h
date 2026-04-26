#pragma once
#include "Entity.h"

class Crystal : public Entity {
public:
    Crystal(Int2 pos);
    ~Crystal() override;

    void Init();
    void Update() override;
    void Draw() override;

    int GetPowerRange() const { return powerRange; }

private:
    int powerRange;
    Texture2D texture;
    bool textureLoaded;
};

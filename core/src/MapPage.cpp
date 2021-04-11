#include "MapPage.h"
#include "glm/glm.hpp"


namespace Core
{  

    MapPage::MapPage(GLuint *cbo) :
        Page("No MapPage name :(("), mMap(nullptr) {

        glGenFramebuffers(1, &mFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

        // cbo is set in editor and passed here
        glBindTexture(GL_TEXTURE_2D, *cbo);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *cbo, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        //addMap(new Map("No Map name :(", glm::vec2(0, 0), 0));
    }

    // Sets mMap to the given map ('map' argument should be created with 'new Map' on the heap)
    Map* MapPage::addMap ( Map *map )
    {
        // Set the old map to have no associated page
        if (mMap) {
            mMap->mAssociatedPage = nullptr;
        }

        mMaps.push_back(map);
        // Set the new map
        mMap = map;

        // Set the new map's associated page
        if (mMap != nullptr) {
            mMap->mAssociatedPage = this;
        }

        return mMap;
    }

    Map* MapPage::getCurrMap() {
        return mMap;
    }

    void MapPage::deleteCurrMap() {
        auto it = std::find(mMaps.begin(), mMaps.end(), mMap);
        if (it != mMaps.end()) { 
            mMaps.erase(it);
        }

        delete mMap;
        mMap = nullptr;
    }

    std::vector<Map*> MapPage::getMaps() {
        return mMaps;
    }

    Camera* MapPage::getCurrCamera() {
        return mMap->getCamera();
    }

    void MapPage::render()
    {
        if (mMap != nullptr) {
            mMap->render(false);
        }

        Page::render();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void MapPage::renderOnFramebuffer ()
    {
        if (mMap != nullptr) {
            if (mFBO >= 0) {
                glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
                glClear(GL_COLOR_BUFFER_BIT);
                mMap->render(true);
            }
            else {
                glClear(GL_COLOR_BUFFER_BIT);
                mMap->render(false);
            }
        }

        Page::render();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // This is called from the MapView window with on a mouse click.
    // x and y are floats on a scale from 0 to 1, indicating the location of the click.
    // The coordinate is a float between 0 and 1 because the MapView window can be stretched, 
    // and we need a predictable scale (0->1 is simple)
    Tile* MapPage::getTileFromClick(float x, float y) {
        glm::ivec2 click(x * 1280, y * 720); // Scale click to pixel coordinates
        return mMap->checkTileCollision(click); // Returns either a ptr to a Tile or nullptr
    }
}
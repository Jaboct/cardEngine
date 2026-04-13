
# cardEngine
There are 2 parts of Card Engine.
- Solitaire (Klondike)
- Oasis (hearthstone clone)


## Solitaire
Solitaire is a simple Klondike clone.
Click on a card to select it.
Click on the card stack in the top left to flip them over one by one.
When you have the next card for the foundation (starting at ace, raising up till king) click on the foundation pile in the bottom center to move the card there.

Render Function:
solitaire_render()
Event Function:
solitaire_event()

![Solitaire example image](https://github.com/Jaboct/jalbSvg/releases/download/Resources/Solitaire_00.png)

## Oasis
Oasis is a simple Hearthstone style clone, specifically a clone of "The League of Explorers" expansion.
Where you construct your deck by selecting your hero, their power, starting packs, and then between each combat you:
expand you deck by adding packs of three cards,
visit the shop to modify existing cards,
add board / character wide passives.

Render Function:
oasis_render()
Event Function:
oasis_event()

![Oasis example image](https://github.com/Jaboct/jalbSvg/releases/download/Resources/Oasis_00.png)

# Framework
This program is built upon a **framework** so there is no main function, instead the render and event functions are called by the framework's render and event loop.


# Libraries
**OpenGL** is the rendering framework called through an api
 struct draw2dStruct \*draw2dApi;

**SDL2** handles the windowing and event handling.



#include "toolTip.h"
#include <sstream>


toolTip::toolTip(serviceLocator* SL)
	:mySL(SL)
{
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0x00000000;
}

void toolTip::update()
{
}

void toolTip::eventUpdate()
{
	if (setup && enabled && tooltipSurface != NULL)
	{
		SDL_GetMouseState(&drawRect.x, &drawRect.y);

		drawRect.x += 10;

		if (drawRect.x + tooltipSurface->w > mySL->globalRenderer.screenWidth)
		{
			drawRect.x = mySL->globalRenderer.screenWidth - tooltipSurface->w;
		}

		if (drawRect.y + tooltipSurface->h > mySL->globalRenderer.screenHeight)
		{
			drawRect.y = mySL->globalRenderer.screenHeight - tooltipSurface->h;
		}

		std::cout << "X: " << drawRect.x << " Y: " << drawRect.y << std::endl;
	}
}

void toolTip::draw()
{
	if (enabled && setup && tooltipSurface != NULL)
	{
		/*SDL_Rect temp;
		temp.x = 0;
		temp.y = 0;
		temp.w = 0;
		temp.h = 0;
		mySL->globalRenderer.drawSurface(bodySurface, temp);*/

		mySL->globalRenderer.drawSurface(tooltipSurface, drawRect);
	}
}

void toolTip::setTitle(std::string newTitle)
{
	titleString = newTitle;
	SDL_Color colour;
	colour.r = 0x50;
	colour.g = 0x50;
	colour.b = 0x50;

	titleSurface = mySL->myImageService.loadText(titleString, colour, mySL->myImageService.UIfont);

	setup = false;

	if (titleSurface == NULL)
	{
		std::cout << "[ERROR]: the title surface was NULL. SDL_ERROR " << SDL_GetError() << std::endl;
	}
}

void toolTip::setBody(std::string newBody)
{
	bodyStrings = wrapText(newBody);
	SDL_Color bodyColour;
	bodyColour.r = 0x6d;
	bodyColour.g = 0x6d;
	bodyColour.b = 0x6d;

	bodySurfaces.clear();

	for (int i = 0; i <= int(bodyStrings.size()) - 1; i++)
	{
		bodySurfaces.push_back(mySL->myImageService.loadText(bodyStrings[i], bodyColour, mySL->myImageService.UIfont_thin));
	}

	setup = false;
}

void toolTip::setFlavorText(std::string newFlavorText)
{
	flavorTextString = wrapText(newFlavorText);

	SDL_Color colour;
	colour.r = 0x27;
	colour.g = 0x27;
	colour.b = 0xe5;

	flavorTextSurfaces.clear();

	for (int i = 0; i <= int(flavorTextString.size()) - 1; i++)
	{
		flavorTextSurfaces.push_back(mySL->myImageService.loadText(flavorTextString[i], colour, mySL->myImageService.UIfont_thin));
	}

	setup = false;
}

void toolTip::setAttribute(std::string attributeText)
{
	SDL_Colour colour;
	colour.r = 0xc7;
	colour.g = 0xc7;
	colour.b = 0xc7;

	attributeString.push_back(attributeText);

	attributeSurfaces.clear();

	for (int i = 0; i <= int(attributeString.size()) - 1; i++)
	{
		attributeSurfaces.push_back(mySL->myImageService.loadText(attributeString[i], colour, mySL->myImageService.UIfont_thin));
	}

	setup = false;
}

std::vector<std::string> toolTip::wrapText(std::string text)
{
	std::string line;
	std::vector<std::string> textList;

	for (int i = 0; i <= int(text.size()) - 1; i++)
	{
		line.push_back(text[i]);
		
		if (text[i + 1] == ' ')
		{
			int w;
			mySL->myImageService.getTextSize(&w, NULL, mySL->myImageService.UIfont_thin, line);
			if (w > maxWidth + widthBuffer)
			{
				textList.push_back(line);
				line = "";
			}
		}
	}

	textList.push_back(line);

	return textList;
}

void toolTip::setupTooltip()
{
	getMaxWidth();
	getMaxHeight();

	tooltipSurface = SDL_CreateRGBSurface(0, drawRect.w, drawRect.h, 32, rmask, gmask, bmask, amask);

	if (drawRect.w > 0 && drawRect.h > 0)
	{
		SDL_BlitScaled(mySL->myImageService.surfaces[mySL->myImageService.blue_panel], NULL, tooltipSurface, &drawRect);

		drawRect.x = widthBuffer;
		drawRect.y = heightBuffer;

		if (titleSurface != NULL)
		{
			SDL_BlitSurface(titleSurface, NULL, tooltipSurface, &drawRect);
			drawRect.y += titleSurface->h;
		}

		for (int i = 0; i <= int(bodySurfaces.size()) - 1; i++)
		{
			SDL_BlitSurface(bodySurfaces[i], NULL, tooltipSurface, &drawRect);
			drawRect.y += bodySurfaces[i]->h + lineSpacing;
		}

		drawRect.y += sectionBuffer;

		for (int i = 0; i <= int(flavorTextSurfaces.size()) - 1; i++)
		{
			SDL_BlitSurface(flavorTextSurfaces[i], NULL, tooltipSurface, &drawRect);
			drawRect.y += flavorTextSurfaces[i]->h + lineSpacing;
		}

		drawRect.y += sectionBuffer;

		for (int i = 0; i <= int(attributeSurfaces.size()) - 1; i++)
		{
			SDL_BlitSurface(attributeSurfaces[i], NULL, tooltipSurface, &drawRect);
			drawRect.y += attributeSurfaces[i]->h + lineSpacing;
		}

		drawRect.y += sectionBuffer;

		setup = true;
	}

	if (tooltipSurface == NULL)
	{
		std::cout << "[ERROR]: the tooltip surface was NULL. SDL_Error " << SDL_GetError() << std::endl;
	}
}

void toolTip::getMaxWidth()
{
	if (titleSurface != NULL)
		drawRect.w = titleSurface->w;

	for (int i = 0; i <= int(bodySurfaces.size()) - 1; i++)
	{
		if (drawRect.w < bodySurfaces[i]->w)
			drawRect.w = bodySurfaces[i]->w;
	}
	
	for (int i = 0; i <= int(flavorTextSurfaces.size()) - 1; i++)
	{
		if (drawRect.w < flavorTextSurfaces[i]->w)
			drawRect.w = flavorTextSurfaces[i]->w;
	}
		

	for (int i = 0; i <= int(attributeSurfaces.size()) - 1; i++)
	{
		if (drawRect.w < attributeSurfaces[i]->w)
			drawRect.w = attributeSurfaces[i]->w;
	}

	//if (drawRect.w > maxWidth)
	//	drawRect.w = maxWidth;

	drawRect.w += widthBuffer * 2;
}

void toolTip::getMaxHeight()
{
	if (titleSurface != NULL)
	{
		drawRect.h += titleSurface->h;
		drawRect.h += sectionBuffer;
	}
		
	if (int(bodySurfaces.size()) > 0)
	{
		drawRect.h += bodySurfaces[0]->h;
		drawRect.h += lineSpacing;

		for (int i = 1; i <= int(bodySurfaces.size()) - 1; i++)
		{
			drawRect.h += lineSpacing;
			drawRect.h += bodySurfaces[i]->h;

			if (i == int(bodySurfaces.size()) - 1)
			{
				drawRect.h += sectionBuffer;
			}
		}
	}

	if (int(flavorTextSurfaces.size()) > 0)
	{
		drawRect.h += flavorTextSurfaces[0]->h;
		drawRect.h += lineSpacing;

		for (int i = 1; i <= int(flavorTextSurfaces.size()) - 1; i++)
		{
			drawRect.h += flavorTextSurfaces[i]->h;
			drawRect.h += lineSpacing;

			if (i == int(flavorTextSurfaces.size()) - 1)
			{
				drawRect.h += sectionBuffer;
			}
		}
	}
	
	if (int(attributeSurfaces.size()) > 0)
	{
		drawRect.h += attributeSurfaces[0]->h;
		drawRect.h += lineSpacing;

		for (int i = 1; i <= int(attributeSurfaces.size()) - 1; i++)
		{
			drawRect.h += lineSpacing;
			drawRect.h += attributeSurfaces[i]->h;
		}
	}
	
	drawRect.h += heightBuffer * 2;

	//if (drawRect.h > maxHeight)
	//	drawRect.h = maxHeight;
}

toolTip::~toolTip()
{
}

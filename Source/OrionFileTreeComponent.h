/*
  ==============================================================================

    OrionFileTreeComponent.h
    Created: 26 Aug 2019 4:43:20pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class OrionFileTreeComponent: public FileTreeComponent,
                            public DragAndDropContainer
{
private:
   
public:
    OrionFileTreeComponent (DirectoryContentsList &listToShow): FileTreeComponent(listToShow){};
    
};

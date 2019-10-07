/*
  ==============================================================================

    OrionFileBrowser.h
    Created: 19 Aug 2019 3:55:36pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class OrionFileBrowser    : public FileBrowserComponent,
                        public DragAndDropContainer,
                        public ChangeBroadcaster
{
    private:
        bool fileDragEnabled;
        TreeView* treeview;
    public:
    OrionFileBrowser(int flags, const File &initialFileOrDirectory, int whatever,FilePreviewComponent *previewComp): FileBrowserComponent (flags, initialFileOrDirectory, nullptr, previewComp),fileDragEnabled (false)
    {
        addMouseListener (this, true);
        treeview = static_cast<TreeView*> (static_cast<FileTreeComponent*> (this->getDisplayComponent()));
        
    };
    
    ~OrionFileBrowser() override {};
    bool shouldDropFilesWhenDraggedExternally(const DragAndDropTarget::SourceDetails & sourceDetails, StringArray & files, bool & canMoveFiles) override
    {
        return true;
    };
    
    
    void mouseDrag (const MouseEvent& ) override //why is component-inherited functions not working??
    
    {
        std::cout<<"is dragging? "<<fileDragEnabled<<"\n";
        if (fileDragEnabled)
        {
            StringArray files;
            
            for (int i = 0; i < getNumSelectedFiles(); i++)
            {
                File file (getSelectedFile (i));
                
                if (file.existsAsFile())
                    files.add (file.getFullPathName());
                    std::cout<<"i got you "<< file.getFullPathName()<<"\n";
            }
            
            fileDragEnabled = false;
            performExternalDragDropOfFiles (files, false);
           
        }
    };
    
    /*
    void mouseDrag (const MouseEvent& e) override
    {
        if (isEnabled()
            && ! (isDragging || e.mouseWasClicked()
                  || e.getDistanceFromDragStart() < 5
                  || e.mods.isPopupMenu()))
        {
            isDragging = true;
            Rectangle<int> pos;
            
            if (auto* item = findItemAt (e.getMouseDownY(), pos))
            {
                if (e.getMouseDownX() >= pos.getX())
                {
                    auto dragDescription = item->getDragSourceDescription();
                    
                    if (! (dragDescription.isVoid() || (dragDescription.isString() && dragDescription.toString().isEmpty())))
                    {
                        if (auto* dragContainer = DragAndDropContainer::findParentDragContainerFor (this))
                        {
                            pos.setSize (pos.getWidth(), item->itemHeight);
                            Image dragImage (Component::createComponentSnapshot (pos, true));
                            dragImage.multiplyAllAlphas (0.6f);
                            
                            auto imageOffset = pos.getPosition() - e.getPosition();
                            dragContainer->startDragging (dragDescription, &owner, dragImage, true, &imageOffset, &e.source);
                        }
                        else
                        {
                            // to be able to do a drag-and-drop operation, the treeview needs to
                            // be inside a component which is also a DragAndDropContainer.
                            std::cout<<"weird "<<owner.getNumRowsInTree()<<"\n";
                            FileTreeComponent* filetree = static_cast<FileTreeComponent*> (&owner);
                            std::cout<<"wtf "<<filetree->getDragAndDropDescription()<<"\n";
                            std::cout<<"huh "<<filetree->getParentComponent()<<"\n";
                            if (auto* dragContainer = DragAndDropContainer::findParentDragContainerFor ( static_cast<TreeView*> (filetree)))
                            {
                                std::cout<<"yes??"<<"\n";
                            }
                            if (auto* dragContainer = DragAndDropContainer::findParentDragContainerFor ( &owner))
                            {
                                std::cout<<"yes"<<"\n";
                            }
                            //this instance is a treeview::contentcomponent
                            jassertfalse;
                        }
                    }
                }
            }
        }
    };
        
     */
        
    void mouseUp (const MouseEvent& /*e*/) override
    {
        fileDragEnabled = false;
    };
    

    
    void fileClicked (const File& /*file*/, const MouseEvent& /*e*/) override
    {
        std::cout<<"hiiiiii? "<<isDragAndDropActive()<<"\n"; //this worked!
        fileDragEnabled = true;
    };
    
    
};




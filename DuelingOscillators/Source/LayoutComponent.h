/*
  ==============================================================================

    LayoutComponent.h
    Created: 14 Feb 2017 1:13:52am
    Author:  Ed

  ==============================================================================
*/

#ifndef LAYOUTCOMPONENT_H_INCLUDED
#define LAYOUTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class LayoutComponent    : public Component
{
public:
    LayoutComponent();
    ~LayoutComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LayoutComponent)
};


#endif  // LAYOUTCOMPONENT_H_INCLUDED

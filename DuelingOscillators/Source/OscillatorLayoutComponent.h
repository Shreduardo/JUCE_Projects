/*
  ==============================================================================

    OscillatorLayoutComponent.h
    Created: 14 Feb 2017 1:15:03am
    Author:  Ed

  ==============================================================================
*/

#ifndef OSCILLATORLAYOUTCOMPONENT_H_INCLUDED
#define OSCILLATORLAYOUTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OscillatorLayoutComponent    : public Component
{
public:
    OscillatorLayoutComponent();
    ~OscillatorLayoutComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorLayoutComponent)
};


#endif  // OSCILLATORLAYOUTCOMPONENT_H_INCLUDED

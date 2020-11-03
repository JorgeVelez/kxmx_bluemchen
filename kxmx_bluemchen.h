#pragma once
#ifndef KXMX_BLUEMCHEN_BSP_H
#define KXMX_BLUEMCHEN_BSP_H
#include "daisy_seed.h"

namespace kxmx
{

class Bluemchen
{
  public:
    /** Enum of Ctrls to represent the four CV/Knob combos on the Patch
     */
    enum Ctrl
    {
        CTRL_1,    /**< */
        CTRL_2,    /**< */
        CTRL_3,    /**< */
        CTRL_4,    /**< */
        CTRL_LAST, /**< */
    };

    /** Daisy patch gate inputs */
    enum GateInput
    {
        GATE_IN_1,    /**< */
        GATE_IN_2,    /** <*/
        GATE_IN_LAST, /**< */
    };

    /** Constructor */
    Bluemchen() {}
    /** Destructor */
    ~Bluemchen() {}

    /** Initializes the daisy seed, and patch hardware.*/
    void Init();

    /** 
    Wait some ms before going on.
    \param del Delay time in ms.
    */
    void DelayMs(size_t del);

    /** Audio Block size defaults to 48.
    Change it using this function before StartingAudio
    \param size Audio block size.
    */
    void SetAudioBlockSize(size_t size);

    /** Starts the callback
    \cb multichannel callback function
    */
    void StartAudio(daisy::AudioHandle::AudioCallback cb);

    /**
       Switch callback functions
       \param cb New multichannel callback function.
    */
    void ChangeAudioCallback(daisy::AudioHandle::AudioCallback cb);

    /** Start analog to digital conversion.*/
    void StartAdc();

    // Hardware Accessors
    /** Get sample rate */
    float AudioSampleRate();
    /** Get block size */
    size_t AudioBlockSize();
    /** Get callback rate */
    float AudioCallbackRate();
    /** Call at same rate as reading controls for good reads. */
    void UpdateAnalogControls();
    /**
       Get value for a particular control
       \param k Which control to get
     */
    float GetCtrlValue(Ctrl k);

    /** Debounce analog controls. Call at same rate as reading controls.*/
    void DebounceControls();

    /* These are exposed for the user to access and manipulate directly
       Helper functions above provide easier access to much of what they are capable of.
    */
    daisy::DaisySeed     seed;                     /**< Seed object */
    daisy::Encoder       encoder;                  /**< Encoder object */
    daisy::AnalogControl controls[CTRL_LAST];      /**< Array of controls*/
    daisy::MidiHandler   midi;                     /**< Handles midi*/
    // daisy::OledDisplay   display;                  /**< & */


  private:
    void InitAudio();
    void InitControls();
    void InitDisplay();
    void InitMidi();
    void InitEncoder();

    dsy_gpio ak4556_reset_pin_;
    uint32_t screen_update_last_, screen_update_period_;
};

} // namespace kxmx

#endif

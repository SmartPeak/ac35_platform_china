
#ifndef SYSINDEX_H
#define SYSINDEX_H

//---------------------------------------------------------------------------
// system commu
//---------------------------------------------------------------------------
/**
 * @brief GPRS Param Settings
 */
int sysCommu_setGprsParam(void);

/**
 * @brief GPRS Connect
 */
int sysCommu_connectGprs(void);

/**
 * @brief GPRS on/off
 */
int sysCommu_setGprs(void);

/**
 * @brief wifi on/off
 */
int sysCommu_setWifi(void);

//---------------------------------------------------------------------------
// system audio
//---------------------------------------------------------------------------
/**
 * @brief speak volume adjust
 */
int sysAudio_speakAudioSet(void);

/**
 * @brief key sound on/off
 */
int sysAudio_keyAudioSet(void);

/**
 * @brief backLight adjust
 */
int sysAudio_backlightSet(void);

/**
 * @brief Dormancy Settings
 */
int sysAudio_dormancySet(void);

/**
 * @brief tp adjust
 */
int sysAudio_TpAdjust(void);

#endif  //SYSINDEX_H


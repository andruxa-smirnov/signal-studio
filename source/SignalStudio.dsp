# Microsoft Developer Studio Project File - Name="SignalStudio" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SignalStudio - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SignalStudio.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SignalStudio.mak" CFG="SignalStudio - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SignalStudio - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SignalStudio - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SignalStudio - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib shlwapi.lib imagehlp.lib dsound.lib dxguid.lib dxerr8.lib htmlhelp.lib /nologo /subsystem:windows /map /debug /machine:I386 /largeaddressaware
# SUBTRACT LINK32 /pdb:none /incremental:yes
# Begin Special Build Tool
OutDir=.\Release
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Desc=copying DLLs
PostBuild_Cmds=copy "$(WkspDir)\..\libsndfile\libsndfile-1.dll" $(OutDir) & copy "$(WkspDir)\..\libsamplerate\libsamplerate-0.dll" $(OutDir) & copy "$(WkspDir)\..\libmad\libmad.dll" $(OutDir) & copy "$(WkspDir)\..\libmp4head\libmp4head\Release\libmp4head.dll" $(OutDir) & copy "$(WkspDir)\..\libid3tag\libid3tag.dll" $(OutDir)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SignalStudio - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib shlwapi.lib imagehlp.lib dsound.lib dxguid.lib dxerr8.lib htmlhelp.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /largeaddressaware
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
OutDir=.\Debug
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Desc=copying DLLs
PostBuild_Cmds=copy "$(WkspDir)\..\libsndfile\libsndfile-1.dll" $(OutDir) & copy "$(WkspDir)\..\libsamplerate\libsamplerate-0.dll" $(OutDir) & copy "$(WkspDir)\..\libmad\libmad.dll" $(OutDir) & copy "$(WkspDir)\..\libmp4head\libmp4head\Debug\libmp4head.dll" $(OutDir) & copy "$(WkspDir)\..\libid3tag\libid3tag.dll" $(OutDir)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "SignalStudio - Win32 Release"
# Name "SignalStudio - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\FnAmplify.cpp
# End Source File
# Begin Source File

SOURCE=.\FnAmplify.h
# End Source File
# Begin Source File

SOURCE=.\ArrayEx.h
# End Source File
# Begin Source File

SOURCE=.\AsyncJob.cpp
# End Source File
# Begin Source File

SOURCE=.\AsyncJob.h
# End Source File
# Begin Source File

SOURCE=.\Benchmark.cpp
# End Source File
# Begin Source File

SOURCE=.\Benchmark.h
# End Source File
# Begin Source File

SOURCE=.\ByteArrayEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ByteArrayEx.h
# End Source File
# Begin Source File

SOURCE=.\FnChangeFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\FnChangeFormat.h
# End Source File
# Begin Source File

SOURCE=.\ChannelBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChannelBar.h
# End Source File
# Begin Source File

SOURCE=.\ChannelRulerController.cpp
# End Source File
# Begin Source File

SOURCE=.\ChannelRulerController.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ClickSliderController.cpp
# End Source File
# Begin Source File

SOURCE=.\ClickSliderController.h
# End Source File
# Begin Source File

SOURCE=.\CoInitializer.h
# End Source File
# Begin Source File

SOURCE=.\ControlResizer.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlResizer.h
# End Source File
# Begin Source File

SOURCE=.\DataTipController.cpp
# End Source File
# Begin Source File

SOURCE=.\DataTipController.h
# End Source File
# Begin Source File

SOURCE=.\BaseDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseDialog.h
# End Source File
# Begin Source File

SOURCE=.\DLLWrap.cpp
# End Source File
# Begin Source File

SOURCE=.\DLLWrap.h
# End Source File
# Begin Source File

SOURCE=.\Dclter.cpp
# End Source File
# Begin Source File

SOURCE=.\Dclter.h
# End Source File
# Begin Source File

SOURCE=.\DocuMan.cpp
# End Source File
# Begin Source File

SOURCE=.\DocuMan.h
# End Source File
# Begin Source File

SOURCE=.\DoubleBufferDC.cpp
# End Source File
# Begin Source File

SOURCE=.\DoubleBufferDC.h
# End Source File
# Begin Source File

SOURCE=.\DPointer.cpp
# End Source File
# Begin Source File

SOURCE=.\DPointer.h
# End Source File
# Begin Source File

SOURCE=.\DragRulerController.cpp
# End Source File
# Begin Source File

SOURCE=.\DragRulerController.h
# End Source File
# Begin Source File

SOURCE=.\DSCap.cpp
# End Source File
# Begin Source File

SOURCE=.\DSCap.h
# End Source File
# Begin Source File

SOURCE=.\DSPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\DSPlayer.h
# End Source File
# Begin Source File

SOURCE=.\EditSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\EditSlider.h
# End Source File
# Begin Source File

SOURCE=.\EditSubitemListController.cpp
# End Source File
# Begin Source File

SOURCE=.\EditSubitemListController.h
# End Source File
# Begin Source File

SOURCE=.\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\ExportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportDlg.h
# End Source File
# Begin Source File

SOURCE=.\CodeFade.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeFade.h
# End Source File
# Begin Source File

SOURCE=.\CodeSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeSearch.h
# End Source File
# Begin Source File

SOURCE=.\CodeFindClipping.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeFindClipping.h
# End Source File
# Begin Source File

SOURCE=.\CodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\BtnFlatIco.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnFlatIco.h
# End Source File
# Begin Source File

SOURCE=.\FocusEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\FocusEditor.h
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderDialog.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\HelpIDs.h
# End Source File
# Begin Source File

SOURCE=.\HelpResMapper.h
# End Source File
# Begin Source File

SOURCE=.\HistoryTool.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryTool.h
# End Source File
# Begin Source File

SOURCE=.\Hyperlink.cpp
# End Source File
# Begin Source File

SOURCE=.\Hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\id3tag.h
# End Source File
# Begin Source File

SOURCE=.\id3tagDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\id3tagFunctions.h
# End Source File
# Begin Source File

SOURCE=.\ID3TagWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\ID3TagWrapper.h
# End Source File
# Begin Source File

SOURCE=.\CodeInsertSilence.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeInsertSilence.h
# End Source File
# Begin Source File

SOURCE=.\kiss_fft\kiss_fft.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\kiss_fft\kiss_fft.h
# End Source File
# Begin Source File

SOURCE=.\kiss_fft\kiss_fftr.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\kiss_fft\kiss_fftr.h
# End Source File
# Begin Source File

SOURCE=.\KissFFT.h
# End Source File
# Begin Source File

SOURCE=.\KissFFTWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\ladspa.h
# End Source File
# Begin Source File

SOURCE=.\lame.h
# End Source File
# Begin Source File

SOURCE=.\lameDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\lameFunctions.h
# End Source File
# Begin Source File

SOURCE=.\LameWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\LameWrapper.h
# End Source File
# Begin Source File

SOURCE=.\libmp4head.h
# End Source File
# Begin Source File

SOURCE=.\mad.h
# End Source File
# Begin Source File

SOURCE=.\madDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\madFunctions.h
# End Source File
# Begin Source File

SOURCE=.\MadWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MadWrapper.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\CodeMetadataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeMetadataDlg.h
# End Source File
# Begin Source File

SOURCE=.\MetadataStrhead.h
# End Source File
# Begin Source File

SOURCE=.\CodeMeterBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeMeterBar.h
# End Source File
# Begin Source File

SOURCE=.\CodeViewMeter.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeViewMeter.h
# End Source File
# Begin Source File

SOURCE=.\CodeLibMiss.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeLibMiss.h
# End Source File
# Begin Source File

SOURCE=.\CodeMP3Encode.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeMP3Encode.h
# End Source File
# Begin Source File

SOURCE=.\MP4DecoderDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\MP4DecoderFunctions.h
# End Source File
# Begin Source File

SOURCE=.\MP4DecoderWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MP4DecoderWrapper.h
# End Source File
# Begin Source File

SOURCE=.\SizingControllerBar.cpp
# End Source File
# Begin Source File

SOURCE=.\SizingControllerBar.h
# End Source File
# Begin Source File

SOURCE=.\NavBar.cpp
# End Source File
# Begin Source File

SOURCE=.\NavBar.h
# End Source File
# Begin Source File

SOURCE=.\neaacdec.h
# End Source File
# Begin Source File

SOURCE=.\CodeNormalize.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeNormalize.h
# End Source File
# Begin Source File

SOURCE=.\NumEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\NumEdit.h
# End Source File
# Begin Source File

SOURCE=.\NumFormatter.cpp
# End Source File
# Begin Source File

SOURCE=.\NumFormatter.h
# End Source File
# Begin Source File

SOURCE=.\CodeOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeOptions.h
# End Source File
# Begin Source File

SOURCE=.\CodeOptionsInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeOptionsInfo.h
# End Source File
# Begin Source File

SOURCE=.\OptPages.h
# End Source File
# Begin Source File

SOURCE=.\OptAudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptAudioDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptCodeRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\OptCodeRecord.h
# End Source File
# Begin Source File

SOURCE=.\OptRTSADlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptRTSADlg.h
# End Source File
# Begin Source File

SOURCE=.\OptViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\Oscillator.cpp
# End Source File
# Begin Source File

SOURCE=.\Oscillator.h
# End Source File
# Begin Source File

SOURCE=.\CodeStrPath.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeStrPath.h
# End Source File
# Begin Source File

SOURCE=.\CodePeakStats.cpp
# End Source File
# Begin Source File

SOURCE=.\CodePeakStats.h
# End Source File
# Begin Source File

SOURCE=.\Persist.cpp
# End Source File
# Begin Source File

SOURCE=.\Persist.h
# End Source File
# Begin Source File

SOURCE=.\CodePersist.cpp
# End Source File
# Begin Source File

SOURCE=.\CodePersist.h
# End Source File
# Begin Source File

SOURCE=.\CodeSetPitch.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeSetPitch.h
# End Source File
# Begin Source File

SOURCE=.\PlotCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PlotCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=.\Plugin.h
# End Source File
# Begin Source File

SOURCE=.\PluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\PluginManager.h
# End Source File
# Begin Source File

SOURCE=.\PluginParamControl.cpp
# End Source File
# Begin Source File

SOURCE=.\PluginParamControl.h
# End Source File
# Begin Source File

SOURCE=.\PluginParameters.cpp
# End Source File
# Begin Source File

SOURCE=.\PluginParameters.h
# End Source File
# Begin Source File

SOURCE=.\PluginParamsViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\PluginParamsViewer.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\CodeRandomList.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeRandomList.h
# End Source File
# Begin Source File

SOURCE=.\Range.h
# End Source File
# Begin Source File

SOURCE=.\CodeRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeRecord.h
# End Source File
# Begin Source File

SOURCE=.\RefPtr.h
# End Source File
# Begin Source File

SOURCE=.\ReportControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportControl.h
# End Source File
# Begin Source File

SOURCE=.\CodeResample.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeResample.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\CodeViewResults.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeViewResults.h
# End Source File
# Begin Source File

SOURCE=.\ResultsReportControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ResultsReportControl.h
# End Source File
# Begin Source File

SOURCE=.\RingBuf.h
# End Source File
# Begin Source File

SOURCE=.\CodeRMSStats.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeRMSStats.h
# End Source File
# Begin Source File

SOURCE=.\Round.h
# End Source File
# Begin Source File

SOURCE=.\CodeRuler.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeRuler.h
# End Source File
# Begin Source File

SOURCE=.\CodeRulerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeRulerControl.h
# End Source File
# Begin Source File

SOURCE=.\samplerate.h
# End Source File
# Begin Source File

SOURCE=.\samplerateDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\CodeSampleRate.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeSampleRate.h
# End Source File
# Begin Source File

SOURCE=.\samplerateFunctions.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\sndfile.h
# End Source File
# Begin Source File

SOURCE=.\CodeSndfileDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\CodeSndFile.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeSndFile.h
# End Source File
# Begin Source File

SOURCE=.\SignalFileFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalFileFormat.h
# End Source File
# Begin Source File

SOURCE=.\sndfileFunctions.h
# End Source File
# Begin Source File

SOURCE=.\SortArray.h
# End Source File
# Begin Source File

SOURCE=.\SortStringArray.cpp
# End Source File
# Begin Source File

SOURCE=.\SortStringArray.h
# End Source File
# Begin Source File

SOURCE=.\AudioDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\UISpeakers.cpp
# End Source File
# Begin Source File

SOURCE=.\UISpeakers.h
# End Source File
# Begin Source File

SOURCE=.\FnAnalyze.cpp
# End Source File
# Begin Source File

SOURCE=.\FnAnalyze.h
# End Source File
# Begin Source File

SOURCE=.\CodeSpectrum.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeSpectrum.h
# End Source File
# Begin Source File

SOURCE=.\UISpectrum.cpp
# End Source File
# Begin Source File

SOURCE=.\UISpectrum.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StubFileLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\StubFileLocation.h
# End Source File
# Begin Source File

SOURCE=.\UIChannelsSwap.cpp
# End Source File
# Begin Source File

SOURCE=.\UIChannelsSwap.h
# End Source File
# Begin Source File

SOURCE=.\CodeShade.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeShade.h
# End Source File
# Begin Source File

SOURCE=.\UISweepAction.cpp
# End Source File
# Begin Source File

SOURCE=.\UISweepAction.h
# End Source File
# Begin Source File

SOURCE=.\TimeCodeRuler.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeCodeRuler.h
# End Source File
# Begin Source File

SOURCE=.\TimeCodeRulerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeCodeRulerControl.h
# End Source File
# Begin Source File

SOURCE=.\Retractable.cpp
# End Source File
# Begin Source File

SOURCE=.\Retractable.h
# End Source File
# Begin Source File

SOURCE=.\RDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\FnR.h
# End Source File
# Begin Source File

SOURCE=.\RetractManager.cpp
# End Source File
# Begin Source File

SOURCE=.\RetractManager.h
# End Source File
# Begin Source File

SOURCE=.\StateReverse.cpp
# End Source File
# Begin Source File

SOURCE=.\StateReverse.h
# End Source File
# Begin Source File

SOURCE=.\TestRetract.cpp
# End Source File
# Begin Source File

SOURCE=.\TestRetract.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\VersionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\VersionInfo.h
# End Source File
# Begin Source File

SOURCE=.\ShowColours.h
# End Source File
# Begin Source File

SOURCE=.\UIShowColours.cpp
# End Source File
# Begin Source File

SOURCE=.\UIShowColours.h
# End Source File
# Begin Source File

SOURCE=.\AudioBar.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioBar.h
# End Source File
# Begin Source File

SOURCE=.\Wave.cpp
# End Source File
# Begin Source File

SOURCE=.\Wave.h
# End Source File
# Begin Source File

SOURCE=.\WaveEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveEdit.h
# End Source File
# Begin Source File

SOURCE=.\UISignalGen.cpp
# End Source File
# Begin Source File

SOURCE=.\UISignalGen.h
# End Source File
# Begin Source File

SOURCE=.\UISignalGenOsc.cpp
# End Source File
# Begin Source File

SOURCE=.\UISignalGenOsc.h
# End Source File
# Begin Source File

SOURCE=.\SignalGenParameters.h
# End Source File
# Begin Source File

SOURCE=.\SignalProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalProcess.h
# End Source File
# Begin Source File

SOURCE=.\SignalStudio.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalStudio.h
# End Source File
# Begin Source File

SOURCE=.\SignalStudio.rc
# End Source File
# Begin Source File

SOURCE=.\SignalStudioDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalStudioDoc.h
# End Source File
# Begin Source File

SOURCE=.\SignalStudioView.cpp
# End Source File
# Begin Source File

SOURCE=.\SignalStudioView.h
# End Source File
# Begin Source File

SOURCE=.\Win32Console.cpp
# End Source File
# Begin Source File

SOURCE=.\Win32Console.h
# End Source File
# Begin Source File

SOURCE=.\WinAppEx.cpp
# End Source File
# Begin Source File

SOURCE=.\WinAppEx.h
# End Source File
# Begin Source File

SOURCE=.\WindowFuncData.h
# End Source File
# Begin Source File

SOURCE=.\WObject.h
# End Source File
# Begin Source File

SOURCE=.\WorkerThread.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkerThread.h
# End Source File
# Begin Source File

SOURCE=.\Boundsx64.h
# End Source File
# Begin Source File

SOURCE=.\ZoomCodeRulerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomCodeRulerControl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\header_sort.bmp
# End Source File
# Begin Source File

SOURCE=.\res\history_pos.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mute_down.ico
# End Source File
# Begin Source File

SOURCE=.\res\mute_up.ico
# End Source File
# Begin Source File

SOURCE=.\res\nav_show_length.ico
# End Source File
# Begin Source File

SOURCE=.\res\tool_zoom.cur
# End Source File
# Begin Source File

SOURCE=.\res\tool_zoom_in.cur
# End Source File
# Begin Source File

SOURCE=.\res\tool_zoom_out.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Transport.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SignalStudio.ico
# End Source File
# Begin Source File

SOURCE=.\res\SignalStudio.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SignalStudioDoc.ico
# End Source File
# End Group
# End Target
# End Project

// @generated

pub const XlibSpecificationRelease: u32 = 6;
pub const X_PROTOCOL: u32 = 11;
pub const X_PROTOCOL_REVISION: u32 = 0;
pub const None: u32 = 0;
pub const ParentRelative: u32 = 1;
pub const CopyFromParent: u32 = 0;
pub const PointerWindow: u32 = 0;
pub const InputFocus: u32 = 1;
pub const PointerRoot: u32 = 1;
pub const AnyPropertyType: u32 = 0;
pub const AnyKey: u32 = 0;
pub const AnyButton: u32 = 0;
pub const AllTemporary: u32 = 0;
pub const CurrentTime: u32 = 0;
pub const NoSymbol: u32 = 0;
pub const NoEventMask: u32 = 0;
pub const KeyPressMask: u32 = 1;
pub const KeyReleaseMask: u32 = 2;
pub const ButtonPressMask: u32 = 4;
pub const ButtonReleaseMask: u32 = 8;
pub const EnterWindowMask: u32 = 16;
pub const LeaveWindowMask: u32 = 32;
pub const PointerMotionMask: u32 = 64;
pub const PointerMotionHintMask: u32 = 128;
pub const Button1MotionMask: u32 = 256;
pub const Button2MotionMask: u32 = 512;
pub const Button3MotionMask: u32 = 1024;
pub const Button4MotionMask: u32 = 2048;
pub const Button5MotionMask: u32 = 4096;
pub const ButtonMotionMask: u32 = 8192;
pub const KeymapStateMask: u32 = 16384;
pub const ExposureMask: u32 = 32768;
pub const VisibilityChangeMask: u32 = 65536;
pub const StructureNotifyMask: u32 = 131072;
pub const ResizeRedirectMask: u32 = 262144;
pub const SubstructureNotifyMask: u32 = 524288;
pub const SubstructureRedirectMask: u32 = 1048576;
pub const FocusChangeMask: u32 = 2097152;
pub const PropertyChangeMask: u32 = 4194304;
pub const ColormapChangeMask: u32 = 8388608;
pub const OwnerGrabButtonMask: u32 = 16777216;
pub const KeyPress: u32 = 2;
pub const KeyRelease: u32 = 3;
pub const ButtonPress: u32 = 4;
pub const ButtonRelease: u32 = 5;
pub const MotionNotify: u32 = 6;
pub const EnterNotify: u32 = 7;
pub const LeaveNotify: u32 = 8;
pub const FocusIn: u32 = 9;
pub const FocusOut: u32 = 10;
pub const KeymapNotify: u32 = 11;
pub const Expose: u32 = 12;
pub const GraphicsExpose: u32 = 13;
pub const NoExpose: u32 = 14;
pub const VisibilityNotify: u32 = 15;
pub const CreateNotify: u32 = 16;
pub const DestroyNotify: u32 = 17;
pub const UnmapNotify: u32 = 18;
pub const MapNotify: u32 = 19;
pub const MapRequest: u32 = 20;
pub const ReparentNotify: u32 = 21;
pub const ConfigureNotify: u32 = 22;
pub const ConfigureRequest: u32 = 23;
pub const GravityNotify: u32 = 24;
pub const ResizeRequest: u32 = 25;
pub const CirculateNotify: u32 = 26;
pub const CirculateRequest: u32 = 27;
pub const PropertyNotify: u32 = 28;
pub const SelectionClear: u32 = 29;
pub const SelectionRequest: u32 = 30;
pub const SelectionNotify: u32 = 31;
pub const ColormapNotify: u32 = 32;
pub const ClientMessage: u32 = 33;
pub const MappingNotify: u32 = 34;
pub const GenericEvent: u32 = 35;
pub const LASTEvent: u32 = 36;
pub const ShiftMask: u32 = 1;
pub const LockMask: u32 = 2;
pub const ControlMask: u32 = 4;
pub const Mod1Mask: u32 = 8;
pub const Mod2Mask: u32 = 16;
pub const Mod3Mask: u32 = 32;
pub const Mod4Mask: u32 = 64;
pub const Mod5Mask: u32 = 128;
pub const ShiftMapIndex: u32 = 0;
pub const LockMapIndex: u32 = 1;
pub const ControlMapIndex: u32 = 2;
pub const Mod1MapIndex: u32 = 3;
pub const Mod2MapIndex: u32 = 4;
pub const Mod3MapIndex: u32 = 5;
pub const Mod4MapIndex: u32 = 6;
pub const Mod5MapIndex: u32 = 7;
pub const Button1Mask: u32 = 256;
pub const Button2Mask: u32 = 512;
pub const Button3Mask: u32 = 1024;
pub const Button4Mask: u32 = 2048;
pub const Button5Mask: u32 = 4096;
pub const AnyModifier: u32 = 32768;
pub const Button1: u32 = 1;
pub const Button2: u32 = 2;
pub const Button3: u32 = 3;
pub const Button4: u32 = 4;
pub const Button5: u32 = 5;
pub const NotifyNormal: u32 = 0;
pub const NotifyGrab: u32 = 1;
pub const NotifyUngrab: u32 = 2;
pub const NotifyWhileGrabbed: u32 = 3;
pub const NotifyHint: u32 = 1;
pub const NotifyAncestor: u32 = 0;
pub const NotifyVirtual: u32 = 1;
pub const NotifyInferior: u32 = 2;
pub const NotifyNonlinear: u32 = 3;
pub const NotifyNonlinearVirtual: u32 = 4;
pub const NotifyPointer: u32 = 5;
pub const NotifyPointerRoot: u32 = 6;
pub const NotifyDetailNone: u32 = 7;
pub const VisibilityUnobscured: u32 = 0;
pub const VisibilityPartiallyObscured: u32 = 1;
pub const VisibilityFullyObscured: u32 = 2;
pub const PlaceOnTop: u32 = 0;
pub const PlaceOnBottom: u32 = 1;
pub const FamilyInternet: u32 = 0;
pub const FamilyDECnet: u32 = 1;
pub const FamilyChaos: u32 = 2;
pub const FamilyInternet6: u32 = 6;
pub const FamilyServerInterpreted: u32 = 5;
pub const PropertyNewValue: u32 = 0;
pub const PropertyDelete: u32 = 1;
pub const ColormapUninstalled: u32 = 0;
pub const ColormapInstalled: u32 = 1;
pub const GrabModeSync: u32 = 0;
pub const GrabModeAsync: u32 = 1;
pub const GrabSuccess: u32 = 0;
pub const AlreadyGrabbed: u32 = 1;
pub const GrabInvalidTime: u32 = 2;
pub const GrabNotViewable: u32 = 3;
pub const GrabFrozen: u32 = 4;
pub const AsyncPointer: u32 = 0;
pub const SyncPointer: u32 = 1;
pub const ReplayPointer: u32 = 2;
pub const AsyncKeyboard: u32 = 3;
pub const SyncKeyboard: u32 = 4;
pub const ReplayKeyboard: u32 = 5;
pub const AsyncBoth: u32 = 6;
pub const SyncBoth: u32 = 7;
pub const RevertToParent: u32 = 2;
pub const Success: u32 = 0;
pub const BadRequest: u32 = 1;
pub const BadValue: u32 = 2;
pub const BadWindow: u32 = 3;
pub const BadPixmap: u32 = 4;
pub const BadAtom: u32 = 5;
pub const BadCursor: u32 = 6;
pub const BadFont: u32 = 7;
pub const BadMatch: u32 = 8;
pub const BadDrawable: u32 = 9;
pub const BadAccess: u32 = 10;
pub const BadAlloc: u32 = 11;
pub const BadColor: u32 = 12;
pub const BadGC: u32 = 13;
pub const BadIDChoice: u32 = 14;
pub const BadName: u32 = 15;
pub const BadLength: u32 = 16;
pub const BadImplementation: u32 = 17;
pub const FirstExtensionError: u32 = 128;
pub const LastExtensionError: u32 = 255;
pub const InputOutput: u32 = 1;
pub const InputOnly: u32 = 2;
pub const CWBackPixmap: u32 = 1;
pub const CWBackPixel: u32 = 2;
pub const CWBorderPixmap: u32 = 4;
pub const CWBorderPixel: u32 = 8;
pub const CWBitGravity: u32 = 16;
pub const CWWinGravity: u32 = 32;
pub const CWBackingStore: u32 = 64;
pub const CWBackingPlanes: u32 = 128;
pub const CWBackingPixel: u32 = 256;
pub const CWOverrideRedirect: u32 = 512;
pub const CWSaveUnder: u32 = 1024;
pub const CWEventMask: u32 = 2048;
pub const CWDontPropagate: u32 = 4096;
pub const CWColormap: u32 = 8192;
pub const CWCursor: u32 = 16384;
pub const CWX: u32 = 1;
pub const CWY: u32 = 2;
pub const CWWidth: u32 = 4;
pub const CWHeight: u32 = 8;
pub const CWBorderWidth: u32 = 16;
pub const CWSibling: u32 = 32;
pub const CWStackMode: u32 = 64;
pub const ForgetGravity: u32 = 0;
pub const NorthWestGravity: u32 = 1;
pub const NorthGravity: u32 = 2;
pub const NorthEastGravity: u32 = 3;
pub const WestGravity: u32 = 4;
pub const CenterGravity: u32 = 5;
pub const EastGravity: u32 = 6;
pub const SouthWestGravity: u32 = 7;
pub const SouthGravity: u32 = 8;
pub const SouthEastGravity: u32 = 9;
pub const StaticGravity: u32 = 10;
pub const UnmapGravity: u32 = 0;
pub const NotUseful: u32 = 0;
pub const WhenMapped: u32 = 1;
pub const Always: u32 = 2;
pub const IsUnmapped: u32 = 0;
pub const IsUnviewable: u32 = 1;
pub const IsViewable: u32 = 2;
pub const SetModeInsert: u32 = 0;
pub const SetModeDelete: u32 = 1;
pub const DestroyAll: u32 = 0;
pub const RetainPermanent: u32 = 1;
pub const RetainTemporary: u32 = 2;
pub const Above: u32 = 0;
pub const Below: u32 = 1;
pub const TopIf: u32 = 2;
pub const BottomIf: u32 = 3;
pub const Opposite: u32 = 4;
pub const RaiseLowest: u32 = 0;
pub const LowerHighest: u32 = 1;
pub const PropModeReplace: u32 = 0;
pub const PropModePrepend: u32 = 1;
pub const PropModeAppend: u32 = 2;
pub const GXclear: u32 = 0;
pub const GXand: u32 = 1;
pub const GXandReverse: u32 = 2;
pub const GXcopy: u32 = 3;
pub const GXandInverted: u32 = 4;
pub const GXnoop: u32 = 5;
pub const GXxor: u32 = 6;
pub const GXor: u32 = 7;
pub const GXnor: u32 = 8;
pub const GXequiv: u32 = 9;
pub const GXinvert: u32 = 10;
pub const GXorReverse: u32 = 11;
pub const GXcopyInverted: u32 = 12;
pub const GXorInverted: u32 = 13;
pub const GXnand: u32 = 14;
pub const GXset: u32 = 15;
pub const LineSolid: u32 = 0;
pub const LineOnOffDash: u32 = 1;
pub const LineDoubleDash: u32 = 2;
pub const CapNotLast: u32 = 0;
pub const CapButt: u32 = 1;
pub const CapRound: u32 = 2;
pub const CapProjecting: u32 = 3;
pub const JoinMiter: u32 = 0;
pub const JoinRound: u32 = 1;
pub const JoinBevel: u32 = 2;
pub const FillSolid: u32 = 0;
pub const FillTiled: u32 = 1;
pub const FillStippled: u32 = 2;
pub const FillOpaqueStippled: u32 = 3;
pub const EvenOddRule: u32 = 0;
pub const WindingRule: u32 = 1;
pub const ClipByChildren: u32 = 0;
pub const IncludeInferiors: u32 = 1;
pub const Unsorted: u32 = 0;
pub const YSorted: u32 = 1;
pub const YXSorted: u32 = 2;
pub const YXBanded: u32 = 3;
pub const CoordModeOrigin: u32 = 0;
pub const CoordModePrevious: u32 = 1;
pub const Complex: u32 = 0;
pub const Nonconvex: u32 = 1;
pub const Convex: u32 = 2;
pub const ArcChord: u32 = 0;
pub const ArcPieSlice: u32 = 1;
pub const GCFunction: u32 = 1;
pub const GCPlaneMask: u32 = 2;
pub const GCForeground: u32 = 4;
pub const GCBackground: u32 = 8;
pub const GCLineWidth: u32 = 16;
pub const GCLineStyle: u32 = 32;
pub const GCCapStyle: u32 = 64;
pub const GCJoinStyle: u32 = 128;
pub const GCFillStyle: u32 = 256;
pub const GCFillRule: u32 = 512;
pub const GCTile: u32 = 1024;
pub const GCStipple: u32 = 2048;
pub const GCTileStipXOrigin: u32 = 4096;
pub const GCTileStipYOrigin: u32 = 8192;
pub const GCFont: u32 = 16384;
pub const GCSubwindowMode: u32 = 32768;
pub const GCGraphicsExposures: u32 = 65536;
pub const GCClipXOrigin: u32 = 131072;
pub const GCClipYOrigin: u32 = 262144;
pub const GCClipMask: u32 = 524288;
pub const GCDashOffset: u32 = 1048576;
pub const GCDashList: u32 = 2097152;
pub const GCArcMode: u32 = 4194304;
pub const GCLastBit: u32 = 22;
pub const FontLeftToRight: u32 = 0;
pub const FontRightToLeft: u32 = 1;
pub const FontChange: u32 = 255;
pub const XYBitmap: u32 = 0;
pub const XYPixmap: u32 = 1;
pub const ZPixmap: u32 = 2;
pub const AllocNone: u32 = 0;
pub const AllocAll: u32 = 1;
pub const DoRed: u32 = 1;
pub const DoGreen: u32 = 2;
pub const DoBlue: u32 = 4;
pub const CursorShape: u32 = 0;
pub const TileShape: u32 = 1;
pub const StippleShape: u32 = 2;
pub const AutoRepeatModeOff: u32 = 0;
pub const AutoRepeatModeOn: u32 = 1;
pub const AutoRepeatModeDefault: u32 = 2;
pub const LedModeOff: u32 = 0;
pub const LedModeOn: u32 = 1;
pub const KBKeyClickPercent: u32 = 1;
pub const KBBellPercent: u32 = 2;
pub const KBBellPitch: u32 = 4;
pub const KBBellDuration: u32 = 8;
pub const KBLed: u32 = 16;
pub const KBLedMode: u32 = 32;
pub const KBKey: u32 = 64;
pub const KBAutoRepeatMode: u32 = 128;
pub const MappingSuccess: u32 = 0;
pub const MappingBusy: u32 = 1;
pub const MappingFailed: u32 = 2;
pub const MappingModifier: u32 = 0;
pub const MappingKeyboard: u32 = 1;
pub const MappingPointer: u32 = 2;
pub const DontPreferBlanking: u32 = 0;
pub const PreferBlanking: u32 = 1;
pub const DefaultBlanking: u32 = 2;
pub const DisableScreenSaver: u32 = 0;
pub const DisableScreenInterval: u32 = 0;
pub const DontAllowExposures: u32 = 0;
pub const AllowExposures: u32 = 1;
pub const DefaultExposures: u32 = 2;
pub const ScreenSaverReset: u32 = 0;
pub const ScreenSaverActive: u32 = 1;
pub const HostInsert: u32 = 0;
pub const HostDelete: u32 = 1;
pub const EnableAccess: u32 = 1;
pub const DisableAccess: u32 = 0;
pub const StaticGray: u32 = 0;
pub const GrayScale: u32 = 1;
pub const StaticColor: u32 = 2;
pub const PseudoColor: u32 = 3;
pub const TrueColor: u32 = 4;
pub const DirectColor: u32 = 5;
pub const LSBFirst: u32 = 0;
pub const MSBFirst: u32 = 1;
pub const NeedFunctionPrototypes: u32 = 1;
pub const NeedVarargsPrototypes: u32 = 1;
pub const NeedNestedPrototypes: u32 = 1;
pub const FUNCPROTO: u32 = 15;
pub const NeedWidePrototypes: u32 = 0;
pub const X_HAVE_UTF8_STRING: u32 = 1;
pub const True: u32 = 1;
pub const False: u32 = 0;
pub const QueuedAlready: u32 = 0;
pub const QueuedAfterReading: u32 = 1;
pub const QueuedAfterFlush: u32 = 2;
pub const XNRequiredCharSet: &[u8; 16] = b"requiredCharSet\0";
pub const XNQueryOrientation: &[u8; 17] = b"queryOrientation\0";
pub const XNBaseFontName: &[u8; 13] = b"baseFontName\0";
pub const XNOMAutomatic: &[u8; 12] = b"omAutomatic\0";
pub const XNMissingCharSet: &[u8; 15] = b"missingCharSet\0";
pub const XNDefaultString: &[u8; 14] = b"defaultString\0";
pub const XNOrientation: &[u8; 12] = b"orientation\0";
pub const XNDirectionalDependentDrawing: &[u8; 28] = b"directionalDependentDrawing\0";
pub const XNContextualDrawing: &[u8; 18] = b"contextualDrawing\0";
pub const XNFontInfo: &[u8; 9] = b"fontInfo\0";
pub const XIMPreeditArea: u32 = 1;
pub const XIMPreeditCallbacks: u32 = 2;
pub const XIMPreeditPosition: u32 = 4;
pub const XIMPreeditNothing: u32 = 8;
pub const XIMPreeditNone: u32 = 16;
pub const XIMStatusArea: u32 = 256;
pub const XIMStatusCallbacks: u32 = 512;
pub const XIMStatusNothing: u32 = 1024;
pub const XIMStatusNone: u32 = 2048;
pub const XNVaNestedList: &[u8; 15] = b"XNVaNestedList\0";
pub const XNQueryInputStyle: &[u8; 16] = b"queryInputStyle\0";
pub const XNClientWindow: &[u8; 13] = b"clientWindow\0";
pub const XNInputStyle: &[u8; 11] = b"inputStyle\0";
pub const XNFocusWindow: &[u8; 12] = b"focusWindow\0";
pub const XNResourceName: &[u8; 13] = b"resourceName\0";
pub const XNResourceClass: &[u8; 14] = b"resourceClass\0";
pub const XNGeometryCallback: &[u8; 17] = b"geometryCallback\0";
pub const XNDestroyCallback: &[u8; 16] = b"destroyCallback\0";
pub const XNFilterEvents: &[u8; 13] = b"filterEvents\0";
pub const XNPreeditStartCallback: &[u8; 21] = b"preeditStartCallback\0";
pub const XNPreeditDoneCallback: &[u8; 20] = b"preeditDoneCallback\0";
pub const XNPreeditDrawCallback: &[u8; 20] = b"preeditDrawCallback\0";
pub const XNPreeditCaretCallback: &[u8; 21] = b"preeditCaretCallback\0";
pub const XNPreeditStateNotifyCallback: &[u8; 27] = b"preeditStateNotifyCallback\0";
pub const XNPreeditAttributes: &[u8; 18] = b"preeditAttributes\0";
pub const XNStatusStartCallback: &[u8; 20] = b"statusStartCallback\0";
pub const XNStatusDoneCallback: &[u8; 19] = b"statusDoneCallback\0";
pub const XNStatusDrawCallback: &[u8; 19] = b"statusDrawCallback\0";
pub const XNStatusAttributes: &[u8; 17] = b"statusAttributes\0";
pub const XNArea: &[u8; 5] = b"area\0";
pub const XNAreaNeeded: &[u8; 11] = b"areaNeeded\0";
pub const XNSpotLocation: &[u8; 13] = b"spotLocation\0";
pub const XNColormap: &[u8; 9] = b"colorMap\0";
pub const XNStdColormap: &[u8; 12] = b"stdColorMap\0";
pub const XNForeground: &[u8; 11] = b"foreground\0";
pub const XNBackground: &[u8; 11] = b"background\0";
pub const XNBackgroundPixmap: &[u8; 17] = b"backgroundPixmap\0";
pub const XNFontSet: &[u8; 8] = b"fontSet\0";
pub const XNLineSpace: &[u8; 10] = b"lineSpace\0";
pub const XNCursor: &[u8; 7] = b"cursor\0";
pub const XNQueryIMValuesList: &[u8; 18] = b"queryIMValuesList\0";
pub const XNQueryICValuesList: &[u8; 18] = b"queryICValuesList\0";
pub const XNVisiblePosition: &[u8; 16] = b"visiblePosition\0";
pub const XNR6PreeditCallback: &[u8; 18] = b"r6PreeditCallback\0";
pub const XNStringConversionCallback: &[u8; 25] = b"stringConversionCallback\0";
pub const XNStringConversion: &[u8; 17] = b"stringConversion\0";
pub const XNResetState: &[u8; 11] = b"resetState\0";
pub const XNHotKey: &[u8; 7] = b"hotKey\0";
pub const XNHotKeyState: &[u8; 12] = b"hotKeyState\0";
pub const XNPreeditState: &[u8; 13] = b"preeditState\0";
pub const XNSeparatorofNestedList: &[u8; 22] = b"separatorofNestedList\0";
pub const XBufferOverflow: i32 = -1;
pub const XLookupNone: u32 = 1;
pub const XLookupChars: u32 = 2;
pub const XLookupKeySym: u32 = 3;
pub const XLookupBoth: u32 = 4;
pub const XIMReverse: u32 = 1;
pub const XIMUnderline: u32 = 2;
pub const XIMHighlight: u32 = 4;
pub const XIMPrimary: u32 = 32;
pub const XIMSecondary: u32 = 64;
pub const XIMTertiary: u32 = 128;
pub const XIMVisibleToForward: u32 = 256;
pub const XIMVisibleToBackword: u32 = 512;
pub const XIMVisibleToCenter: u32 = 1024;
pub const XIMPreeditUnKnown: u32 = 0;
pub const XIMPreeditEnable: u32 = 1;
pub const XIMPreeditDisable: u32 = 2;
pub const XIMInitialState: u32 = 1;
pub const XIMPreserveState: u32 = 2;
pub const XIMStringConversionLeftEdge: u32 = 1;
pub const XIMStringConversionRightEdge: u32 = 2;
pub const XIMStringConversionTopEdge: u32 = 4;
pub const XIMStringConversionBottomEdge: u32 = 8;
pub const XIMStringConversionConcealed: u32 = 16;
pub const XIMStringConversionWrapped: u32 = 32;
pub const XIMStringConversionBuffer: u32 = 1;
pub const XIMStringConversionLine: u32 = 2;
pub const XIMStringConversionWord: u32 = 3;
pub const XIMStringConversionChar: u32 = 4;
pub const XIMStringConversionSubstitution: u32 = 1;
pub const XIMStringConversionRetrieval: u32 = 2;
pub const XIMHotKeyStateON: u32 = 1;
pub const XIMHotKeyStateOFF: u32 = 2;
pub type XID = std::os::raw::c_ulong;
pub type Mask = std::os::raw::c_ulong;
pub type Atom = std::os::raw::c_ulong;
pub type VisualID = std::os::raw::c_ulong;
pub type Time = std::os::raw::c_ulong;
pub type Window = XID;
pub type Drawable = XID;
pub type Font = XID;
pub type Pixmap = XID;
pub type Cursor = XID;
pub type Colormap = XID;
pub type GContext = XID;
pub type KeySym = XID;
pub type KeyCode = std::os::raw::c_uchar;
pub type wchar_t = std::os::raw::c_uint;
extern "C" {
    pub fn _Xmblen(
        str_: *mut std::os::raw::c_char,
        len: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
pub type XPointer = *mut std::os::raw::c_char;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XExtData {
    pub number: std::os::raw::c_int,
    pub next: *mut _XExtData,
    pub free_private: ::std::option::Option<
        unsafe extern "C" fn(extension: *mut _XExtData) -> std::os::raw::c_int,
    >,
    pub private_data: XPointer,
}
impl Default for _XExtData {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XExtData = _XExtData;
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XExtCodes {
    pub extension: std::os::raw::c_int,
    pub major_opcode: std::os::raw::c_int,
    pub first_event: std::os::raw::c_int,
    pub first_error: std::os::raw::c_int,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XPixmapFormatValues {
    pub depth: std::os::raw::c_int,
    pub bits_per_pixel: std::os::raw::c_int,
    pub scanline_pad: std::os::raw::c_int,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XGCValues {
    pub function: std::os::raw::c_int,
    pub plane_mask: std::os::raw::c_ulong,
    pub foreground: std::os::raw::c_ulong,
    pub background: std::os::raw::c_ulong,
    pub line_width: std::os::raw::c_int,
    pub line_style: std::os::raw::c_int,
    pub cap_style: std::os::raw::c_int,
    pub join_style: std::os::raw::c_int,
    pub fill_style: std::os::raw::c_int,
    pub fill_rule: std::os::raw::c_int,
    pub arc_mode: std::os::raw::c_int,
    pub tile: Pixmap,
    pub stipple: Pixmap,
    pub ts_x_origin: std::os::raw::c_int,
    pub ts_y_origin: std::os::raw::c_int,
    pub font: Font,
    pub subwindow_mode: std::os::raw::c_int,
    pub graphics_exposures: std::os::raw::c_int,
    pub clip_x_origin: std::os::raw::c_int,
    pub clip_y_origin: std::os::raw::c_int,
    pub clip_mask: Pixmap,
    pub dash_offset: std::os::raw::c_int,
    pub dashes: std::os::raw::c_char,
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XGC {
    _unused: [u8; 0],
}
pub type GC = *mut _XGC;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct Visual {
    pub ext_data: *mut XExtData,
    pub visualid: VisualID,
    pub class: std::os::raw::c_int,
    pub red_mask: std::os::raw::c_ulong,
    pub green_mask: std::os::raw::c_ulong,
    pub blue_mask: std::os::raw::c_ulong,
    pub bits_per_rgb: std::os::raw::c_int,
    pub map_entries: std::os::raw::c_int,
}
impl Default for Visual {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct Depth {
    pub depth: std::os::raw::c_int,
    pub nvisuals: std::os::raw::c_int,
    pub visuals: *mut Visual,
}
impl Default for Depth {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XDisplay {
    _unused: [u8; 0],
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct Screen {
    pub ext_data: *mut XExtData,
    pub display: *mut _XDisplay,
    pub root: Window,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub mwidth: std::os::raw::c_int,
    pub mheight: std::os::raw::c_int,
    pub ndepths: std::os::raw::c_int,
    pub depths: *mut Depth,
    pub root_depth: std::os::raw::c_int,
    pub root_visual: *mut Visual,
    pub default_gc: GC,
    pub cmap: Colormap,
    pub white_pixel: std::os::raw::c_ulong,
    pub black_pixel: std::os::raw::c_ulong,
    pub max_maps: std::os::raw::c_int,
    pub min_maps: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub save_unders: std::os::raw::c_int,
    pub root_input_mask: std::os::raw::c_long,
}
impl Default for Screen {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct ScreenFormat {
    pub ext_data: *mut XExtData,
    pub depth: std::os::raw::c_int,
    pub bits_per_pixel: std::os::raw::c_int,
    pub scanline_pad: std::os::raw::c_int,
}
impl Default for ScreenFormat {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XSetWindowAttributes {
    pub background_pixmap: Pixmap,
    pub background_pixel: std::os::raw::c_ulong,
    pub border_pixmap: Pixmap,
    pub border_pixel: std::os::raw::c_ulong,
    pub bit_gravity: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub backing_planes: std::os::raw::c_ulong,
    pub backing_pixel: std::os::raw::c_ulong,
    pub save_under: std::os::raw::c_int,
    pub event_mask: std::os::raw::c_long,
    pub do_not_propagate_mask: std::os::raw::c_long,
    pub override_redirect: std::os::raw::c_int,
    pub colormap: Colormap,
    pub cursor: Cursor,
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XWindowAttributes {
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub depth: std::os::raw::c_int,
    pub visual: *mut Visual,
    pub root: Window,
    pub class: std::os::raw::c_int,
    pub bit_gravity: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub backing_planes: std::os::raw::c_ulong,
    pub backing_pixel: std::os::raw::c_ulong,
    pub save_under: std::os::raw::c_int,
    pub colormap: Colormap,
    pub map_installed: std::os::raw::c_int,
    pub map_state: std::os::raw::c_int,
    pub all_event_masks: std::os::raw::c_long,
    pub your_event_mask: std::os::raw::c_long,
    pub do_not_propagate_mask: std::os::raw::c_long,
    pub override_redirect: std::os::raw::c_int,
    pub screen: *mut Screen,
}
impl Default for XWindowAttributes {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XHostAddress {
    pub family: std::os::raw::c_int,
    pub length: std::os::raw::c_int,
    pub address: *mut std::os::raw::c_char,
}
impl Default for XHostAddress {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XServerInterpretedAddress {
    pub typelength: std::os::raw::c_int,
    pub valuelength: std::os::raw::c_int,
    pub type_: *mut std::os::raw::c_char,
    pub value: *mut std::os::raw::c_char,
}
impl Default for XServerInterpretedAddress {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XImage {
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub xoffset: std::os::raw::c_int,
    pub format: std::os::raw::c_int,
    pub data: *mut std::os::raw::c_char,
    pub byte_order: std::os::raw::c_int,
    pub bitmap_unit: std::os::raw::c_int,
    pub bitmap_bit_order: std::os::raw::c_int,
    pub bitmap_pad: std::os::raw::c_int,
    pub depth: std::os::raw::c_int,
    pub bytes_per_line: std::os::raw::c_int,
    pub bits_per_pixel: std::os::raw::c_int,
    pub red_mask: std::os::raw::c_ulong,
    pub green_mask: std::os::raw::c_ulong,
    pub blue_mask: std::os::raw::c_ulong,
    pub obdata: XPointer,
    pub f: _XImage_funcs,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct _XImage_funcs {
    pub create_image: ::std::option::Option<
        unsafe extern "C" fn(
            arg1: *mut _XDisplay,
            arg2: *mut Visual,
            arg3: std::os::raw::c_uint,
            arg4: std::os::raw::c_int,
            arg5: std::os::raw::c_int,
            arg6: *mut std::os::raw::c_char,
            arg7: std::os::raw::c_uint,
            arg8: std::os::raw::c_uint,
            arg9: std::os::raw::c_int,
            arg10: std::os::raw::c_int,
        ) -> *mut _XImage,
    >,
    pub destroy_image:
        ::std::option::Option<unsafe extern "C" fn(arg1: *mut _XImage) -> std::os::raw::c_int>,
    pub get_pixel: ::std::option::Option<
        unsafe extern "C" fn(
            arg1: *mut _XImage,
            arg2: std::os::raw::c_int,
            arg3: std::os::raw::c_int,
        ) -> std::os::raw::c_ulong,
    >,
    pub put_pixel: ::std::option::Option<
        unsafe extern "C" fn(
            arg1: *mut _XImage,
            arg2: std::os::raw::c_int,
            arg3: std::os::raw::c_int,
            arg4: std::os::raw::c_ulong,
        ) -> std::os::raw::c_int,
    >,
    pub sub_image: ::std::option::Option<
        unsafe extern "C" fn(
            arg1: *mut _XImage,
            arg2: std::os::raw::c_int,
            arg3: std::os::raw::c_int,
            arg4: std::os::raw::c_uint,
            arg5: std::os::raw::c_uint,
        ) -> *mut _XImage,
    >,
    pub add_pixel: ::std::option::Option<
        unsafe extern "C" fn(arg1: *mut _XImage, arg2: std::os::raw::c_long) -> std::os::raw::c_int,
    >,
}
impl Default for _XImage {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XImage = _XImage;
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XWindowChanges {
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub sibling: Window,
    pub stack_mode: std::os::raw::c_int,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XColor {
    pub pixel: std::os::raw::c_ulong,
    pub red: std::os::raw::c_ushort,
    pub green: std::os::raw::c_ushort,
    pub blue: std::os::raw::c_ushort,
    pub flags: std::os::raw::c_char,
    pub pad: std::os::raw::c_char,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XSegment {
    pub x1: std::os::raw::c_short,
    pub y1: std::os::raw::c_short,
    pub x2: std::os::raw::c_short,
    pub y2: std::os::raw::c_short,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XPoint {
    pub x: std::os::raw::c_short,
    pub y: std::os::raw::c_short,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XRectangle {
    pub x: std::os::raw::c_short,
    pub y: std::os::raw::c_short,
    pub width: std::os::raw::c_ushort,
    pub height: std::os::raw::c_ushort,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XArc {
    pub x: std::os::raw::c_short,
    pub y: std::os::raw::c_short,
    pub width: std::os::raw::c_ushort,
    pub height: std::os::raw::c_ushort,
    pub angle1: std::os::raw::c_short,
    pub angle2: std::os::raw::c_short,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XKeyboardControl {
    pub key_click_percent: std::os::raw::c_int,
    pub bell_percent: std::os::raw::c_int,
    pub bell_pitch: std::os::raw::c_int,
    pub bell_duration: std::os::raw::c_int,
    pub led: std::os::raw::c_int,
    pub led_mode: std::os::raw::c_int,
    pub key: std::os::raw::c_int,
    pub auto_repeat_mode: std::os::raw::c_int,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XKeyboardState {
    pub key_click_percent: std::os::raw::c_int,
    pub bell_percent: std::os::raw::c_int,
    pub bell_pitch: std::os::raw::c_uint,
    pub bell_duration: std::os::raw::c_uint,
    pub led_mask: std::os::raw::c_ulong,
    pub global_auto_repeat: std::os::raw::c_int,
    pub auto_repeats: [std::os::raw::c_char; 32usize],
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XTimeCoord {
    pub time: Time,
    pub x: std::os::raw::c_short,
    pub y: std::os::raw::c_short,
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XModifierKeymap {
    pub max_keypermod: std::os::raw::c_int,
    pub modifiermap: *mut KeyCode,
}
impl Default for XModifierKeymap {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type Display = _XDisplay;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XPrivate {
    _unused: [u8; 0],
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XrmHashBucketRec {
    _unused: [u8; 0],
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _bindgen_ty_1 {
    pub ext_data: *mut XExtData,
    pub private1: *mut _XPrivate,
    pub fd: std::os::raw::c_int,
    pub private2: std::os::raw::c_int,
    pub proto_major_version: std::os::raw::c_int,
    pub proto_minor_version: std::os::raw::c_int,
    pub vendor: *mut std::os::raw::c_char,
    pub private3: XID,
    pub private4: XID,
    pub private5: XID,
    pub private6: std::os::raw::c_int,
    pub resource_alloc: ::std::option::Option<unsafe extern "C" fn(arg1: *mut _XDisplay) -> XID>,
    pub byte_order: std::os::raw::c_int,
    pub bitmap_unit: std::os::raw::c_int,
    pub bitmap_pad: std::os::raw::c_int,
    pub bitmap_bit_order: std::os::raw::c_int,
    pub nformats: std::os::raw::c_int,
    pub pixmap_format: *mut ScreenFormat,
    pub private8: std::os::raw::c_int,
    pub release: std::os::raw::c_int,
    pub private9: *mut _XPrivate,
    pub private10: *mut _XPrivate,
    pub qlen: std::os::raw::c_int,
    pub last_request_read: std::os::raw::c_ulong,
    pub request: std::os::raw::c_ulong,
    pub private11: XPointer,
    pub private12: XPointer,
    pub private13: XPointer,
    pub private14: XPointer,
    pub max_request_size: std::os::raw::c_uint,
    pub db: *mut _XrmHashBucketRec,
    pub private15:
        ::std::option::Option<unsafe extern "C" fn(arg1: *mut _XDisplay) -> std::os::raw::c_int>,
    pub display_name: *mut std::os::raw::c_char,
    pub default_screen: std::os::raw::c_int,
    pub nscreens: std::os::raw::c_int,
    pub screens: *mut Screen,
    pub motion_buffer: std::os::raw::c_ulong,
    pub private16: std::os::raw::c_ulong,
    pub min_keycode: std::os::raw::c_int,
    pub max_keycode: std::os::raw::c_int,
    pub private17: XPointer,
    pub private18: XPointer,
    pub private19: std::os::raw::c_int,
    pub xdefaults: *mut std::os::raw::c_char,
}
impl Default for _bindgen_ty_1 {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type _XPrivDisplay = *mut _bindgen_ty_1;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XKeyEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub keycode: std::os::raw::c_uint,
    pub same_screen: std::os::raw::c_int,
}
impl Default for XKeyEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XKeyPressedEvent = XKeyEvent;
pub type XKeyReleasedEvent = XKeyEvent;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XButtonEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub button: std::os::raw::c_uint,
    pub same_screen: std::os::raw::c_int,
}
impl Default for XButtonEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XButtonPressedEvent = XButtonEvent;
pub type XButtonReleasedEvent = XButtonEvent;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XMotionEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub is_hint: std::os::raw::c_char,
    pub same_screen: std::os::raw::c_int,
}
impl Default for XMotionEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XPointerMovedEvent = XMotionEvent;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XCrossingEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub mode: std::os::raw::c_int,
    pub detail: std::os::raw::c_int,
    pub same_screen: std::os::raw::c_int,
    pub focus: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
}
impl Default for XCrossingEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XEnterWindowEvent = XCrossingEvent;
pub type XLeaveWindowEvent = XCrossingEvent;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XFocusChangeEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub mode: std::os::raw::c_int,
    pub detail: std::os::raw::c_int,
}
impl Default for XFocusChangeEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XFocusInEvent = XFocusChangeEvent;
pub type XFocusOutEvent = XFocusChangeEvent;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XKeymapEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub key_vector: [std::os::raw::c_char; 32usize],
}
impl Default for XKeymapEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XExposeEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
}
impl Default for XExposeEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XGraphicsExposeEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub drawable: Drawable,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
    pub major_code: std::os::raw::c_int,
    pub minor_code: std::os::raw::c_int,
}
impl Default for XGraphicsExposeEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XNoExposeEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub drawable: Drawable,
    pub major_code: std::os::raw::c_int,
    pub minor_code: std::os::raw::c_int,
}
impl Default for XNoExposeEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XVisibilityEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub state: std::os::raw::c_int,
}
impl Default for XVisibilityEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XCreateWindowEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub override_redirect: std::os::raw::c_int,
}
impl Default for XCreateWindowEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XDestroyWindowEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
}
impl Default for XDestroyWindowEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XUnmapEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub from_configure: std::os::raw::c_int,
}
impl Default for XUnmapEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XMapEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub override_redirect: std::os::raw::c_int,
}
impl Default for XMapEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XMapRequestEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
}
impl Default for XMapRequestEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XReparentEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub parent: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub override_redirect: std::os::raw::c_int,
}
impl Default for XReparentEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XConfigureEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub above: Window,
    pub override_redirect: std::os::raw::c_int,
}
impl Default for XConfigureEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XGravityEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
}
impl Default for XGravityEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XResizeRequestEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
}
impl Default for XResizeRequestEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XConfigureRequestEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub above: Window,
    pub detail: std::os::raw::c_int,
    pub value_mask: std::os::raw::c_ulong,
}
impl Default for XConfigureRequestEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XCirculateEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub place: std::os::raw::c_int,
}
impl Default for XCirculateEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XCirculateRequestEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub place: std::os::raw::c_int,
}
impl Default for XCirculateRequestEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XPropertyEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub atom: Atom,
    pub time: Time,
    pub state: std::os::raw::c_int,
}
impl Default for XPropertyEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XSelectionClearEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub selection: Atom,
    pub time: Time,
}
impl Default for XSelectionClearEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XSelectionRequestEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub owner: Window,
    pub requestor: Window,
    pub selection: Atom,
    pub target: Atom,
    pub property: Atom,
    pub time: Time,
}
impl Default for XSelectionRequestEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XSelectionEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub requestor: Window,
    pub selection: Atom,
    pub target: Atom,
    pub property: Atom,
    pub time: Time,
}
impl Default for XSelectionEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XColormapEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub colormap: Colormap,
    pub new: std::os::raw::c_int,
    pub state: std::os::raw::c_int,
}
impl Default for XColormapEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Copy, Clone)]
pub struct XClientMessageEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub message_type: Atom,
    pub format: std::os::raw::c_int,
    pub data: XClientMessageEvent__bindgen_ty_1,
}
#[repr(C)]
#[derive(Copy, Clone)]
pub union XClientMessageEvent__bindgen_ty_1 {
    pub b: [std::os::raw::c_char; 20usize],
    pub s: [std::os::raw::c_short; 10usize],
    pub l: [std::os::raw::c_long; 5usize],
}
impl Default for XClientMessageEvent__bindgen_ty_1 {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for XClientMessageEvent__bindgen_ty_1 {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(f, "XClientMessageEvent__bindgen_ty_1 {{ union }}")
    }
}
impl Default for XClientMessageEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for XClientMessageEvent {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write ! (f , "XClientMessageEvent {{ type: {:?}, serial: {:?}, send_event: {:?}, display: {:?}, window: {:?}, message_type: {:?}, format: {:?}, data: {:?} }}" , self . type_ , self . serial , self . send_event , self . display , self . window , self . message_type , self . format , self . data)
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XMappingEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub request: std::os::raw::c_int,
    pub first_keycode: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
}
impl Default for XMappingEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XErrorEvent {
    pub type_: std::os::raw::c_int,
    pub display: *mut Display,
    pub resourceid: XID,
    pub serial: std::os::raw::c_ulong,
    pub error_code: std::os::raw::c_uchar,
    pub request_code: std::os::raw::c_uchar,
    pub minor_code: std::os::raw::c_uchar,
}
impl Default for XErrorEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XAnyEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
}
impl Default for XAnyEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XGenericEvent {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub extension: std::os::raw::c_int,
    pub evtype: std::os::raw::c_int,
}
impl Default for XGenericEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XGenericEventCookie {
    pub type_: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub extension: std::os::raw::c_int,
    pub evtype: std::os::raw::c_int,
    pub cookie: std::os::raw::c_uint,
    pub data: *mut std::os::raw::c_void,
}
impl Default for XGenericEventCookie {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Copy, Clone)]
pub union _XEvent {
    pub type_: std::os::raw::c_int,
    pub xany: XAnyEvent,
    pub xkey: XKeyEvent,
    pub xbutton: XButtonEvent,
    pub xmotion: XMotionEvent,
    pub xcrossing: XCrossingEvent,
    pub xfocus: XFocusChangeEvent,
    pub xexpose: XExposeEvent,
    pub xgraphicsexpose: XGraphicsExposeEvent,
    pub xnoexpose: XNoExposeEvent,
    pub xvisibility: XVisibilityEvent,
    pub xcreatewindow: XCreateWindowEvent,
    pub xdestroywindow: XDestroyWindowEvent,
    pub xunmap: XUnmapEvent,
    pub xmap: XMapEvent,
    pub xmaprequest: XMapRequestEvent,
    pub xreparent: XReparentEvent,
    pub xconfigure: XConfigureEvent,
    pub xgravity: XGravityEvent,
    pub xresizerequest: XResizeRequestEvent,
    pub xconfigurerequest: XConfigureRequestEvent,
    pub xcirculate: XCirculateEvent,
    pub xcirculaterequest: XCirculateRequestEvent,
    pub xproperty: XPropertyEvent,
    pub xselectionclear: XSelectionClearEvent,
    pub xselectionrequest: XSelectionRequestEvent,
    pub xselection: XSelectionEvent,
    pub xcolormap: XColormapEvent,
    pub xclient: XClientMessageEvent,
    pub xmapping: XMappingEvent,
    pub xerror: XErrorEvent,
    pub xkeymap: XKeymapEvent,
    pub xgeneric: XGenericEvent,
    pub xcookie: XGenericEventCookie,
    pub pad: [std::os::raw::c_long; 24usize],
}
impl Default for _XEvent {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XEvent {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(f, "_XEvent {{ union }}")
    }
}
pub type XEvent = _XEvent;
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XCharStruct {
    pub lbearing: std::os::raw::c_short,
    pub rbearing: std::os::raw::c_short,
    pub width: std::os::raw::c_short,
    pub ascent: std::os::raw::c_short,
    pub descent: std::os::raw::c_short,
    pub attributes: std::os::raw::c_ushort,
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XFontProp {
    pub name: Atom,
    pub card32: std::os::raw::c_ulong,
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XFontStruct {
    pub ext_data: *mut XExtData,
    pub fid: Font,
    pub direction: std::os::raw::c_uint,
    pub min_char_or_byte2: std::os::raw::c_uint,
    pub max_char_or_byte2: std::os::raw::c_uint,
    pub min_byte1: std::os::raw::c_uint,
    pub max_byte1: std::os::raw::c_uint,
    pub all_chars_exist: std::os::raw::c_int,
    pub default_char: std::os::raw::c_uint,
    pub n_properties: std::os::raw::c_int,
    pub properties: *mut XFontProp,
    pub min_bounds: XCharStruct,
    pub max_bounds: XCharStruct,
    pub per_char: *mut XCharStruct,
    pub ascent: std::os::raw::c_int,
    pub descent: std::os::raw::c_int,
}
impl Default for XFontStruct {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XTextItem {
    pub chars: *mut std::os::raw::c_char,
    pub nchars: std::os::raw::c_int,
    pub delta: std::os::raw::c_int,
    pub font: Font,
}
impl Default for XTextItem {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XChar2b {
    pub byte1: std::os::raw::c_uchar,
    pub byte2: std::os::raw::c_uchar,
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XTextItem16 {
    pub chars: *mut XChar2b,
    pub nchars: std::os::raw::c_int,
    pub delta: std::os::raw::c_int,
    pub font: Font,
}
impl Default for XTextItem16 {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Copy, Clone)]
pub union XEDataObject {
    pub display: *mut Display,
    pub gc: GC,
    pub visual: *mut Visual,
    pub screen: *mut Screen,
    pub pixmap_format: *mut ScreenFormat,
    pub font: *mut XFontStruct,
}
impl Default for XEDataObject {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for XEDataObject {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(f, "XEDataObject {{ union }}")
    }
}
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct XFontSetExtents {
    pub max_ink_extent: XRectangle,
    pub max_logical_extent: XRectangle,
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XOM {
    _unused: [u8; 0],
}
pub type XOM = *mut _XOM;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XOC {
    _unused: [u8; 0],
}
pub type XOC = *mut _XOC;
pub type XFontSet = *mut _XOC;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XmbTextItem {
    pub chars: *mut std::os::raw::c_char,
    pub nchars: std::os::raw::c_int,
    pub delta: std::os::raw::c_int,
    pub font_set: XFontSet,
}
impl Default for XmbTextItem {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XwcTextItem {
    pub chars: *mut wchar_t,
    pub nchars: std::os::raw::c_int,
    pub delta: std::os::raw::c_int,
    pub font_set: XFontSet,
}
impl Default for XwcTextItem {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XOMCharSetList {
    pub charset_count: std::os::raw::c_int,
    pub charset_list: *mut *mut std::os::raw::c_char,
}
impl Default for XOMCharSetList {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub const XOrientation_XOMOrientation_LTR_TTB: XOrientation = 0;
pub const XOrientation_XOMOrientation_RTL_TTB: XOrientation = 1;
pub const XOrientation_XOMOrientation_TTB_LTR: XOrientation = 2;
pub const XOrientation_XOMOrientation_TTB_RTL: XOrientation = 3;
pub const XOrientation_XOMOrientation_Context: XOrientation = 4;
pub type XOrientation = std::os::raw::c_uint;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XOMOrientation {
    pub num_orientation: std::os::raw::c_int,
    pub orientation: *mut XOrientation,
}
impl Default for XOMOrientation {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XOMFontInfo {
    pub num_font: std::os::raw::c_int,
    pub font_struct_list: *mut *mut XFontStruct,
    pub font_name_list: *mut *mut std::os::raw::c_char,
}
impl Default for XOMFontInfo {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XIM {
    _unused: [u8; 0],
}
pub type XIM = *mut _XIM;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XIC {
    _unused: [u8; 0],
}
pub type XIC = *mut _XIC;
pub type XIMProc =
    ::std::option::Option<unsafe extern "C" fn(arg1: XIM, arg2: XPointer, arg3: XPointer)>;
pub type XICProc = ::std::option::Option<
    unsafe extern "C" fn(arg1: XIC, arg2: XPointer, arg3: XPointer) -> std::os::raw::c_int,
>;
pub type XIDProc =
    ::std::option::Option<unsafe extern "C" fn(arg1: *mut Display, arg2: XPointer, arg3: XPointer)>;
pub type XIMStyle = std::os::raw::c_ulong;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XIMStyles {
    pub count_styles: std::os::raw::c_ushort,
    pub supported_styles: *mut XIMStyle,
}
impl Default for XIMStyles {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XVaNestedList = *mut std::os::raw::c_void;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XIMCallback {
    pub client_data: XPointer,
    pub callback: XIMProc,
}
impl Default for XIMCallback {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XICCallback {
    pub client_data: XPointer,
    pub callback: XICProc,
}
impl Default for XICCallback {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XIMFeedback = std::os::raw::c_ulong;
#[repr(C)]
#[derive(Copy, Clone)]
pub struct _XIMText {
    pub length: std::os::raw::c_ushort,
    pub feedback: *mut XIMFeedback,
    pub encoding_is_wchar: std::os::raw::c_int,
    pub string: _XIMText__bindgen_ty_1,
}
#[repr(C)]
#[derive(Copy, Clone)]
pub union _XIMText__bindgen_ty_1 {
    pub multi_byte: *mut std::os::raw::c_char,
    pub wide_char: *mut wchar_t,
}
impl Default for _XIMText__bindgen_ty_1 {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XIMText__bindgen_ty_1 {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(f, "_XIMText__bindgen_ty_1 {{ union }}")
    }
}
impl Default for _XIMText {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XIMText {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(
            f,
            "_XIMText {{ length: {:?}, feedback: {:?}, encoding_is_wchar: {:?}, string: {:?} }}",
            self.length, self.feedback, self.encoding_is_wchar, self.string
        )
    }
}
pub type XIMText = _XIMText;
pub type XIMPreeditState = std::os::raw::c_ulong;
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct _XIMPreeditStateNotifyCallbackStruct {
    pub state: XIMPreeditState,
}
pub type XIMPreeditStateNotifyCallbackStruct = _XIMPreeditStateNotifyCallbackStruct;
pub type XIMResetState = std::os::raw::c_ulong;
pub type XIMStringConversionFeedback = std::os::raw::c_ulong;
#[repr(C)]
#[derive(Copy, Clone)]
pub struct _XIMStringConversionText {
    pub length: std::os::raw::c_ushort,
    pub feedback: *mut XIMStringConversionFeedback,
    pub encoding_is_wchar: std::os::raw::c_int,
    pub string: _XIMStringConversionText__bindgen_ty_1,
}
#[repr(C)]
#[derive(Copy, Clone)]
pub union _XIMStringConversionText__bindgen_ty_1 {
    pub mbs: *mut std::os::raw::c_char,
    pub wcs: *mut wchar_t,
}
impl Default for _XIMStringConversionText__bindgen_ty_1 {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XIMStringConversionText__bindgen_ty_1 {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(f, "_XIMStringConversionText__bindgen_ty_1 {{ union }}")
    }
}
impl Default for _XIMStringConversionText {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XIMStringConversionText {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write ! (f , "_XIMStringConversionText {{ length: {:?}, feedback: {:?}, encoding_is_wchar: {:?}, string: {:?} }}" , self . length , self . feedback , self . encoding_is_wchar , self . string)
    }
}
pub type XIMStringConversionText = _XIMStringConversionText;
pub type XIMStringConversionPosition = std::os::raw::c_ushort;
pub type XIMStringConversionType = std::os::raw::c_ushort;
pub type XIMStringConversionOperation = std::os::raw::c_ushort;
pub const XIMCaretDirection_XIMForwardChar: XIMCaretDirection = 0;
pub const XIMCaretDirection_XIMBackwardChar: XIMCaretDirection = 1;
pub const XIMCaretDirection_XIMForwardWord: XIMCaretDirection = 2;
pub const XIMCaretDirection_XIMBackwardWord: XIMCaretDirection = 3;
pub const XIMCaretDirection_XIMCaretUp: XIMCaretDirection = 4;
pub const XIMCaretDirection_XIMCaretDown: XIMCaretDirection = 5;
pub const XIMCaretDirection_XIMNextLine: XIMCaretDirection = 6;
pub const XIMCaretDirection_XIMPreviousLine: XIMCaretDirection = 7;
pub const XIMCaretDirection_XIMLineStart: XIMCaretDirection = 8;
pub const XIMCaretDirection_XIMLineEnd: XIMCaretDirection = 9;
pub const XIMCaretDirection_XIMAbsolutePosition: XIMCaretDirection = 10;
pub const XIMCaretDirection_XIMDontChange: XIMCaretDirection = 11;
pub type XIMCaretDirection = std::os::raw::c_uint;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XIMStringConversionCallbackStruct {
    pub position: XIMStringConversionPosition,
    pub direction: XIMCaretDirection,
    pub operation: XIMStringConversionOperation,
    pub factor: std::os::raw::c_ushort,
    pub text: *mut XIMStringConversionText,
}
impl Default for _XIMStringConversionCallbackStruct {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XIMStringConversionCallbackStruct = _XIMStringConversionCallbackStruct;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XIMPreeditDrawCallbackStruct {
    pub caret: std::os::raw::c_int,
    pub chg_first: std::os::raw::c_int,
    pub chg_length: std::os::raw::c_int,
    pub text: *mut XIMText,
}
impl Default for _XIMPreeditDrawCallbackStruct {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XIMPreeditDrawCallbackStruct = _XIMPreeditDrawCallbackStruct;
pub const XIMCaretStyle_XIMIsInvisible: XIMCaretStyle = 0;
pub const XIMCaretStyle_XIMIsPrimary: XIMCaretStyle = 1;
pub const XIMCaretStyle_XIMIsSecondary: XIMCaretStyle = 2;
pub type XIMCaretStyle = std::os::raw::c_uint;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XIMPreeditCaretCallbackStruct {
    pub position: std::os::raw::c_int,
    pub direction: XIMCaretDirection,
    pub style: XIMCaretStyle,
}
impl Default for _XIMPreeditCaretCallbackStruct {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XIMPreeditCaretCallbackStruct = _XIMPreeditCaretCallbackStruct;
pub const XIMStatusDataType_XIMTextType: XIMStatusDataType = 0;
pub const XIMStatusDataType_XIMBitmapType: XIMStatusDataType = 1;
pub type XIMStatusDataType = std::os::raw::c_uint;
#[repr(C)]
#[derive(Copy, Clone)]
pub struct _XIMStatusDrawCallbackStruct {
    pub type_: XIMStatusDataType,
    pub data: _XIMStatusDrawCallbackStruct__bindgen_ty_1,
}
#[repr(C)]
#[derive(Copy, Clone)]
pub union _XIMStatusDrawCallbackStruct__bindgen_ty_1 {
    pub text: *mut XIMText,
    pub bitmap: Pixmap,
}
impl Default for _XIMStatusDrawCallbackStruct__bindgen_ty_1 {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XIMStatusDrawCallbackStruct__bindgen_ty_1 {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(f, "_XIMStatusDrawCallbackStruct__bindgen_ty_1 {{ union }}")
    }
}
impl Default for _XIMStatusDrawCallbackStruct {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
impl ::std::fmt::Debug for _XIMStatusDrawCallbackStruct {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        write!(
            f,
            "_XIMStatusDrawCallbackStruct {{ type: {:?}, data: {:?} }}",
            self.type_, self.data
        )
    }
}
pub type XIMStatusDrawCallbackStruct = _XIMStatusDrawCallbackStruct;
#[repr(C)]
#[derive(Debug, Default, Copy, Clone)]
pub struct _XIMHotKeyTrigger {
    pub keysym: KeySym,
    pub modifier: std::os::raw::c_int,
    pub modifier_mask: std::os::raw::c_int,
}
pub type XIMHotKeyTrigger = _XIMHotKeyTrigger;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct _XIMHotKeyTriggers {
    pub num_hot_key: std::os::raw::c_int,
    pub key: *mut XIMHotKeyTrigger,
}
impl Default for _XIMHotKeyTriggers {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
pub type XIMHotKeyTriggers = _XIMHotKeyTriggers;
pub type XIMHotKeyState = std::os::raw::c_ulong;
#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct XIMValuesList {
    pub count_values: std::os::raw::c_ushort,
    pub supported_values: *mut *mut std::os::raw::c_char,
}
impl Default for XIMValuesList {
    fn default() -> Self {
        let mut s = ::std::mem::MaybeUninit::<Self>::uninit();
        unsafe {
            ::std::ptr::write_bytes(s.as_mut_ptr(), 0, 1);
            s.assume_init()
        }
    }
}
extern "C" {
    pub static mut _Xdebug: std::os::raw::c_int;
}
extern "C" {
    pub fn XLoadQueryFont(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
    ) -> *mut XFontStruct;
}
extern "C" {
    pub fn XQueryFont(arg1: *mut Display, arg2: XID) -> *mut XFontStruct;
}
extern "C" {
    pub fn XGetMotionEvents(
        arg1: *mut Display,
        arg2: Window,
        arg3: Time,
        arg4: Time,
        arg5: *mut std::os::raw::c_int,
    ) -> *mut XTimeCoord;
}
extern "C" {
    pub fn XDeleteModifiermapEntry(
        arg1: *mut XModifierKeymap,
        arg2: KeyCode,
        arg3: std::os::raw::c_int,
    ) -> *mut XModifierKeymap;
}
extern "C" {
    pub fn XGetModifierMapping(arg1: *mut Display) -> *mut XModifierKeymap;
}
extern "C" {
    pub fn XInsertModifiermapEntry(
        arg1: *mut XModifierKeymap,
        arg2: KeyCode,
        arg3: std::os::raw::c_int,
    ) -> *mut XModifierKeymap;
}
extern "C" {
    pub fn XNewModifiermap(arg1: std::os::raw::c_int) -> *mut XModifierKeymap;
}
extern "C" {
    pub fn XCreateImage(
        arg1: *mut Display,
        arg2: *mut Visual,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut std::os::raw::c_char,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_uint,
        arg9: std::os::raw::c_int,
        arg10: std::os::raw::c_int,
    ) -> *mut XImage;
}
extern "C" {
    pub fn XInitImage(arg1: *mut XImage) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetImage(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_ulong,
        arg8: std::os::raw::c_int,
    ) -> *mut XImage;
}
extern "C" {
    pub fn XGetSubImage(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_ulong,
        arg8: std::os::raw::c_int,
        arg9: *mut XImage,
        arg10: std::os::raw::c_int,
        arg11: std::os::raw::c_int,
    ) -> *mut XImage;
}
extern "C" {
    pub fn XOpenDisplay(arg1: *const std::os::raw::c_char) -> *mut Display;
}
extern "C" {
    pub fn XrmInitialize();
}
extern "C" {
    pub fn XFetchBytes(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
    ) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XFetchBuffer(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
        arg3: std::os::raw::c_int,
    ) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XGetAtomName(arg1: *mut Display, arg2: Atom) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XGetAtomNames(
        arg1: *mut Display,
        arg2: *mut Atom,
        arg3: std::os::raw::c_int,
        arg4: *mut *mut std::os::raw::c_char,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetDefault(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: *const std::os::raw::c_char,
    ) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XDisplayName(arg1: *const std::os::raw::c_char) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XKeysymToString(arg1: KeySym) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XSynchronize(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
    ) -> ::std::option::Option<
        unsafe extern "C" fn(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int,
    >;
}
extern "C" {
    pub fn XSetAfterFunction(
        arg1: *mut Display,
        arg2: ::std::option::Option<
            unsafe extern "C" fn(arg1: *mut Display) -> std::os::raw::c_int,
        >,
    ) -> ::std::option::Option<
        unsafe extern "C" fn(
            arg1: *mut Display,
            arg2: ::std::option::Option<
                unsafe extern "C" fn(arg1: *mut Display) -> std::os::raw::c_int,
            >,
        ) -> std::os::raw::c_int,
    >;
}
extern "C" {
    pub fn XInternAtom(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> Atom;
}
extern "C" {
    pub fn XInternAtoms(
        arg1: *mut Display,
        arg2: *mut *mut std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: *mut Atom,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCopyColormapAndFree(arg1: *mut Display, arg2: Colormap) -> Colormap;
}
extern "C" {
    pub fn XCreateColormap(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Visual,
        arg4: std::os::raw::c_int,
    ) -> Colormap;
}
extern "C" {
    pub fn XCreatePixmapCursor(
        arg1: *mut Display,
        arg2: Pixmap,
        arg3: Pixmap,
        arg4: *mut XColor,
        arg5: *mut XColor,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
    ) -> Cursor;
}
extern "C" {
    pub fn XCreateGlyphCursor(
        arg1: *mut Display,
        arg2: Font,
        arg3: Font,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_uint,
        arg6: *const XColor,
        arg7: *const XColor,
    ) -> Cursor;
}
extern "C" {
    pub fn XCreateFontCursor(arg1: *mut Display, arg2: std::os::raw::c_uint) -> Cursor;
}
extern "C" {
    pub fn XLoadFont(arg1: *mut Display, arg2: *const std::os::raw::c_char) -> Font;
}
extern "C" {
    pub fn XCreateGC(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_ulong,
        arg4: *mut XGCValues,
    ) -> GC;
}
extern "C" {
    pub fn XGContextFromGC(arg1: GC) -> GContext;
}
extern "C" {
    pub fn XFlushGC(arg1: *mut Display, arg2: GC);
}
extern "C" {
    pub fn XCreatePixmap(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_uint,
    ) -> Pixmap;
}
extern "C" {
    pub fn XCreateBitmapFromData(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: *const std::os::raw::c_char,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_uint,
    ) -> Pixmap;
}
extern "C" {
    pub fn XCreatePixmapFromBitmapData(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: *mut std::os::raw::c_char,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_ulong,
        arg7: std::os::raw::c_ulong,
        arg8: std::os::raw::c_uint,
    ) -> Pixmap;
}
extern "C" {
    pub fn XCreateSimpleWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_ulong,
        arg9: std::os::raw::c_ulong,
    ) -> Window;
}
extern "C" {
    pub fn XGetSelectionOwner(arg1: *mut Display, arg2: Atom) -> Window;
}
extern "C" {
    pub fn XCreateWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_uint,
        arg10: *mut Visual,
        arg11: std::os::raw::c_ulong,
        arg12: *mut XSetWindowAttributes,
    ) -> Window;
}
extern "C" {
    pub fn XListInstalledColormaps(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut std::os::raw::c_int,
    ) -> *mut Colormap;
}
extern "C" {
    pub fn XListFonts(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
    ) -> *mut *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XListFontsWithInfo(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut *mut XFontStruct,
    ) -> *mut *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XGetFontPath(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
    ) -> *mut *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XListExtensions(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
    ) -> *mut *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XListProperties(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut std::os::raw::c_int,
    ) -> *mut Atom;
}
extern "C" {
    pub fn XListHosts(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
    ) -> *mut XHostAddress;
}
extern "C" {
    pub fn XKeycodeToKeysym(arg1: *mut Display, arg2: KeyCode, arg3: std::os::raw::c_int)
        -> KeySym;
}
extern "C" {
    pub fn XLookupKeysym(arg1: *mut XKeyEvent, arg2: std::os::raw::c_int) -> KeySym;
}
extern "C" {
    pub fn XGetKeyboardMapping(
        arg1: *mut Display,
        arg2: KeyCode,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
    ) -> *mut KeySym;
}
extern "C" {
    pub fn XStringToKeysym(arg1: *const std::os::raw::c_char) -> KeySym;
}
extern "C" {
    pub fn XMaxRequestSize(arg1: *mut Display) -> std::os::raw::c_long;
}
extern "C" {
    pub fn XExtendedMaxRequestSize(arg1: *mut Display) -> std::os::raw::c_long;
}
extern "C" {
    pub fn XResourceManagerString(arg1: *mut Display) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XScreenResourceString(arg1: *mut Screen) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XDisplayMotionBufferSize(arg1: *mut Display) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XVisualIDFromVisual(arg1: *mut Visual) -> VisualID;
}
extern "C" {
    pub fn XInitThreads() -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeThreads() -> std::os::raw::c_int;
}
extern "C" {
    pub fn XLockDisplay(arg1: *mut Display);
}
extern "C" {
    pub fn XUnlockDisplay(arg1: *mut Display);
}
extern "C" {
    pub fn XInitExtension(arg1: *mut Display, arg2: *const std::os::raw::c_char) -> *mut XExtCodes;
}
extern "C" {
    pub fn XAddExtension(arg1: *mut Display) -> *mut XExtCodes;
}
extern "C" {
    pub fn XFindOnExtensionList(
        arg1: *mut *mut XExtData,
        arg2: std::os::raw::c_int,
    ) -> *mut XExtData;
}
extern "C" {
    pub fn XEHeadOfExtensionList(arg1: XEDataObject) -> *mut *mut XExtData;
}
extern "C" {
    pub fn XRootWindow(arg1: *mut Display, arg2: std::os::raw::c_int) -> Window;
}
extern "C" {
    pub fn XDefaultRootWindow(arg1: *mut Display) -> Window;
}
extern "C" {
    pub fn XRootWindowOfScreen(arg1: *mut Screen) -> Window;
}
extern "C" {
    pub fn XDefaultVisual(arg1: *mut Display, arg2: std::os::raw::c_int) -> *mut Visual;
}
extern "C" {
    pub fn XDefaultVisualOfScreen(arg1: *mut Screen) -> *mut Visual;
}
extern "C" {
    pub fn XDefaultGC(arg1: *mut Display, arg2: std::os::raw::c_int) -> GC;
}
extern "C" {
    pub fn XDefaultGCOfScreen(arg1: *mut Screen) -> GC;
}
extern "C" {
    pub fn XBlackPixel(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XWhitePixel(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XAllPlanes() -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XBlackPixelOfScreen(arg1: *mut Screen) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XWhitePixelOfScreen(arg1: *mut Screen) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XNextRequest(arg1: *mut Display) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XLastKnownRequestProcessed(arg1: *mut Display) -> std::os::raw::c_ulong;
}
extern "C" {
    pub fn XServerVendor(arg1: *mut Display) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XDisplayString(arg1: *mut Display) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XDefaultColormap(arg1: *mut Display, arg2: std::os::raw::c_int) -> Colormap;
}
extern "C" {
    pub fn XDefaultColormapOfScreen(arg1: *mut Screen) -> Colormap;
}
extern "C" {
    pub fn XDisplayOfScreen(arg1: *mut Screen) -> *mut Display;
}
extern "C" {
    pub fn XScreenOfDisplay(arg1: *mut Display, arg2: std::os::raw::c_int) -> *mut Screen;
}
extern "C" {
    pub fn XDefaultScreenOfDisplay(arg1: *mut Display) -> *mut Screen;
}
extern "C" {
    pub fn XEventMaskOfScreen(arg1: *mut Screen) -> std::os::raw::c_long;
}
extern "C" {
    pub fn XScreenNumberOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
pub type XErrorHandler = ::std::option::Option<
    unsafe extern "C" fn(arg1: *mut Display, arg2: *mut XErrorEvent) -> std::os::raw::c_int,
>;
extern "C" {
    pub fn XSetErrorHandler(arg1: XErrorHandler) -> XErrorHandler;
}
pub type XIOErrorHandler =
    ::std::option::Option<unsafe extern "C" fn(arg1: *mut Display) -> std::os::raw::c_int>;
extern "C" {
    pub fn XSetIOErrorHandler(arg1: XIOErrorHandler) -> XIOErrorHandler;
}
pub type XIOErrorExitHandler = ::std::option::Option<
    unsafe extern "C" fn(arg1: *mut Display, arg2: *mut std::os::raw::c_void),
>;
extern "C" {
    pub fn XSetIOErrorExitHandler(
        arg1: *mut Display,
        arg2: XIOErrorExitHandler,
        arg3: *mut std::os::raw::c_void,
    );
}
extern "C" {
    pub fn XListPixmapFormats(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
    ) -> *mut XPixmapFormatValues;
}
extern "C" {
    pub fn XListDepths(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
    ) -> *mut std::os::raw::c_int;
}
extern "C" {
    pub fn XReconfigureWMWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_uint,
        arg5: *mut XWindowChanges,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetWMProtocols(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut *mut Atom,
        arg4: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWMProtocols(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Atom,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XIconifyWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XWithdrawWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetCommand(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut *mut *mut std::os::raw::c_char,
        arg4: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetWMColormapWindows(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut *mut Window,
        arg4: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWMColormapWindows(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Window,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeStringList(arg1: *mut *mut std::os::raw::c_char);
}
extern "C" {
    pub fn XSetTransientForHint(
        arg1: *mut Display,
        arg2: Window,
        arg3: Window,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XActivateScreenSaver(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAddHost(arg1: *mut Display, arg2: *mut XHostAddress) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAddHosts(
        arg1: *mut Display,
        arg2: *mut XHostAddress,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAddToExtensionList(
        arg1: *mut *mut _XExtData,
        arg2: *mut XExtData,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAddToSaveSet(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAllocColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAllocColorCells(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_ulong,
        arg5: std::os::raw::c_uint,
        arg6: *mut std::os::raw::c_ulong,
        arg7: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAllocColorPlanes(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_ulong,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
        arg8: std::os::raw::c_int,
        arg9: *mut std::os::raw::c_ulong,
        arg10: *mut std::os::raw::c_ulong,
        arg11: *mut std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAllocNamedColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *const std::os::raw::c_char,
        arg4: *mut XColor,
        arg5: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAllowEvents(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAutoRepeatOff(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XAutoRepeatOn(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XBell(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XBitmapBitOrder(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XBitmapPad(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XBitmapUnit(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCellsOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeActivePointerGrab(
        arg1: *mut Display,
        arg2: std::os::raw::c_uint,
        arg3: Cursor,
        arg4: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeGC(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
        arg4: *mut XGCValues,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeKeyboardControl(
        arg1: *mut Display,
        arg2: std::os::raw::c_ulong,
        arg3: *mut XKeyboardControl,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeKeyboardMapping(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: std::os::raw::c_int,
        arg4: *mut KeySym,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangePointerControl(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeProperty(
        arg1: *mut Display,
        arg2: Window,
        arg3: Atom,
        arg4: Atom,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_uchar,
        arg8: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeSaveSet(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XChangeWindowAttributes(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_ulong,
        arg4: *mut XSetWindowAttributes,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCheckIfEvent(
        arg1: *mut Display,
        arg2: *mut XEvent,
        arg3: ::std::option::Option<
            unsafe extern "C" fn(
                arg1: *mut Display,
                arg2: *mut XEvent,
                arg3: XPointer,
            ) -> std::os::raw::c_int,
        >,
        arg4: XPointer,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCheckMaskEvent(
        arg1: *mut Display,
        arg2: std::os::raw::c_long,
        arg3: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCheckTypedEvent(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCheckTypedWindowEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCheckWindowEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_long,
        arg4: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCirculateSubwindows(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCirculateSubwindowsDown(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCirculateSubwindowsUp(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XClearArea(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XClearWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCloseDisplay(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XConfigureWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_uint,
        arg4: *mut XWindowChanges,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XConnectionNumber(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XConvertSelection(
        arg1: *mut Display,
        arg2: Atom,
        arg3: Atom,
        arg4: Atom,
        arg5: Window,
        arg6: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCopyArea(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: Drawable,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_uint,
        arg9: std::os::raw::c_int,
        arg10: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCopyGC(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
        arg4: GC,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XCopyPlane(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: Drawable,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_uint,
        arg9: std::os::raw::c_int,
        arg10: std::os::raw::c_int,
        arg11: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDefaultDepth(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDefaultDepthOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDefaultScreen(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDefineCursor(arg1: *mut Display, arg2: Window, arg3: Cursor) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDeleteProperty(arg1: *mut Display, arg2: Window, arg3: Atom) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDestroyWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDestroySubwindows(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDoesBackingStore(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDoesSaveUnders(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisableAccessControl(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayCells(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayHeight(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayHeightMM(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayKeycodes(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayPlanes(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayWidth(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDisplayWidthMM(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawArc(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawArcs(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XArc,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawImageString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *const std::os::raw::c_char,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawImageString16(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *const XChar2b,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawLine(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawLines(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XPoint,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawPoint(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawPoints(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XPoint,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawRectangle(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawRectangles(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XRectangle,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawSegments(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XSegment,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *const std::os::raw::c_char,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawString16(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *const XChar2b,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawText(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut XTextItem,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDrawText16(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut XTextItem16,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XEnableAccessControl(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XEventsQueued(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFetchName(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut *mut std::os::raw::c_char,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFillArc(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFillArcs(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XArc,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFillPolygon(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XPoint,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFillRectangle(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFillRectangles(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XRectangle,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFlush(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XForceScreenSaver(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFree(arg1: *mut std::os::raw::c_void) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeColormap(arg1: *mut Display, arg2: Colormap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeColors(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut std::os::raw::c_ulong,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeCursor(arg1: *mut Display, arg2: Cursor) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeExtensionList(arg1: *mut *mut std::os::raw::c_char) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeFont(arg1: *mut Display, arg2: *mut XFontStruct) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeFontInfo(
        arg1: *mut *mut std::os::raw::c_char,
        arg2: *mut XFontStruct,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeFontNames(arg1: *mut *mut std::os::raw::c_char) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeFontPath(arg1: *mut *mut std::os::raw::c_char) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeGC(arg1: *mut Display, arg2: GC) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeModifiermap(arg1: *mut XModifierKeymap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreePixmap(arg1: *mut Display, arg2: Pixmap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGeometry(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: *const std::os::raw::c_char,
        arg4: *const std::os::raw::c_char,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_int,
        arg10: *mut std::os::raw::c_int,
        arg11: *mut std::os::raw::c_int,
        arg12: *mut std::os::raw::c_int,
        arg13: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetErrorDatabaseText(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: *const std::os::raw::c_char,
        arg4: *const std::os::raw::c_char,
        arg5: *mut std::os::raw::c_char,
        arg6: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetErrorText(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: *mut std::os::raw::c_char,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetFontProperty(
        arg1: *mut XFontStruct,
        arg2: Atom,
        arg3: *mut std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetGCValues(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
        arg4: *mut XGCValues,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetGeometry(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: *mut Window,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_uint,
        arg7: *mut std::os::raw::c_uint,
        arg8: *mut std::os::raw::c_uint,
        arg9: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetIconName(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut *mut std::os::raw::c_char,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetInputFocus(
        arg1: *mut Display,
        arg2: *mut Window,
        arg3: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetKeyboardControl(
        arg1: *mut Display,
        arg2: *mut XKeyboardState,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetPointerControl(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetPointerMapping(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_uchar,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetScreenSaver(
        arg1: *mut Display,
        arg2: *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetTransientForHint(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Window,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetWindowProperty(
        arg1: *mut Display,
        arg2: Window,
        arg3: Atom,
        arg4: std::os::raw::c_long,
        arg5: std::os::raw::c_long,
        arg6: std::os::raw::c_int,
        arg7: Atom,
        arg8: *mut Atom,
        arg9: *mut std::os::raw::c_int,
        arg10: *mut std::os::raw::c_ulong,
        arg11: *mut std::os::raw::c_ulong,
        arg12: *mut *mut std::os::raw::c_uchar,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetWindowAttributes(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut XWindowAttributes,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGrabButton(
        arg1: *mut Display,
        arg2: std::os::raw::c_uint,
        arg3: std::os::raw::c_uint,
        arg4: Window,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_int,
        arg8: std::os::raw::c_int,
        arg9: Window,
        arg10: Cursor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGrabKey(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: std::os::raw::c_uint,
        arg4: Window,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGrabKeyboard(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGrabPointer(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: Window,
        arg8: Cursor,
        arg9: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGrabServer(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XHeightMMOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XHeightOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XIfEvent(
        arg1: *mut Display,
        arg2: *mut XEvent,
        arg3: ::std::option::Option<
            unsafe extern "C" fn(
                arg1: *mut Display,
                arg2: *mut XEvent,
                arg3: XPointer,
            ) -> std::os::raw::c_int,
        >,
        arg4: XPointer,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XImageByteOrder(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XInstallColormap(arg1: *mut Display, arg2: Colormap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XKeysymToKeycode(arg1: *mut Display, arg2: KeySym) -> KeyCode;
}
extern "C" {
    pub fn XKillClient(arg1: *mut Display, arg2: XID) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XLookupColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *const std::os::raw::c_char,
        arg4: *mut XColor,
        arg5: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XLowerWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMapRaised(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMapSubwindows(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMapWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMaskEvent(
        arg1: *mut Display,
        arg2: std::os::raw::c_long,
        arg3: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMaxCmapsOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMinCmapsOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMoveResizeWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XMoveWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XNextEvent(arg1: *mut Display, arg2: *mut XEvent) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XNoOp(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XParseColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *const std::os::raw::c_char,
        arg4: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XParseGeometry(
        arg1: *const std::os::raw::c_char,
        arg2: *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
        arg4: *mut std::os::raw::c_uint,
        arg5: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XPeekEvent(arg1: *mut Display, arg2: *mut XEvent) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XPeekIfEvent(
        arg1: *mut Display,
        arg2: *mut XEvent,
        arg3: ::std::option::Option<
            unsafe extern "C" fn(
                arg1: *mut Display,
                arg2: *mut XEvent,
                arg3: XPointer,
            ) -> std::os::raw::c_int,
        >,
        arg4: XPointer,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XPending(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XPlanesOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XProtocolRevision(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XProtocolVersion(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XPutBackEvent(arg1: *mut Display, arg2: *mut XEvent) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XPutImage(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XImage,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_uint,
        arg10: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQLength(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryBestCursor(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_uint,
        arg5: *mut std::os::raw::c_uint,
        arg6: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryBestSize(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: Drawable,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_uint,
        arg6: *mut std::os::raw::c_uint,
        arg7: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryBestStipple(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_uint,
        arg5: *mut std::os::raw::c_uint,
        arg6: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryBestTile(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_uint,
        arg5: *mut std::os::raw::c_uint,
        arg6: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryColors(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut XColor,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryExtension(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: *mut std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryKeymap(arg1: *mut Display, arg2: *mut std::os::raw::c_char)
        -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryPointer(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Window,
        arg4: *mut Window,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut std::os::raw::c_int,
        arg9: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryTextExtents(
        arg1: *mut Display,
        arg2: XID,
        arg3: *const std::os::raw::c_char,
        arg4: std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut XCharStruct,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryTextExtents16(
        arg1: *mut Display,
        arg2: XID,
        arg3: *const XChar2b,
        arg4: std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut XCharStruct,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XQueryTree(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Window,
        arg4: *mut Window,
        arg5: *mut *mut Window,
        arg6: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRaiseWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XReadBitmapFile(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: *const std::os::raw::c_char,
        arg4: *mut std::os::raw::c_uint,
        arg5: *mut std::os::raw::c_uint,
        arg6: *mut Pixmap,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XReadBitmapFileData(
        arg1: *const std::os::raw::c_char,
        arg2: *mut std::os::raw::c_uint,
        arg3: *mut std::os::raw::c_uint,
        arg4: *mut *mut std::os::raw::c_uchar,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRebindKeysym(
        arg1: *mut Display,
        arg2: KeySym,
        arg3: *mut KeySym,
        arg4: std::os::raw::c_int,
        arg5: *const std::os::raw::c_uchar,
        arg6: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRecolorCursor(
        arg1: *mut Display,
        arg2: Cursor,
        arg3: *mut XColor,
        arg4: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRefreshKeyboardMapping(arg1: *mut XMappingEvent) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRemoveFromSaveSet(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRemoveHost(arg1: *mut Display, arg2: *mut XHostAddress) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRemoveHosts(
        arg1: *mut Display,
        arg2: *mut XHostAddress,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XReparentWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: Window,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XResetScreenSaver(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XResizeWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRestackWindows(
        arg1: *mut Display,
        arg2: *mut Window,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRotateBuffers(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRotateWindowProperties(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut Atom,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XScreenCount(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSelectInput(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_long,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSendEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_long,
        arg5: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetAccessControl(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetArcMode(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetBackground(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetClipMask(arg1: *mut Display, arg2: GC, arg3: Pixmap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetClipOrigin(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetClipRectangles(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: *mut XRectangle,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetCloseDownMode(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetCommand(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut *mut std::os::raw::c_char,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetDashes(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
        arg4: *const std::os::raw::c_char,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetFillRule(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetFillStyle(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetFont(arg1: *mut Display, arg2: GC, arg3: Font) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetFontPath(
        arg1: *mut Display,
        arg2: *mut *mut std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetForeground(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetFunction(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetGraphicsExposures(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetIconName(
        arg1: *mut Display,
        arg2: Window,
        arg3: *const std::os::raw::c_char,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetInputFocus(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetLineAttributes(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetModifierMapping(
        arg1: *mut Display,
        arg2: *mut XModifierKeymap,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetPlaneMask(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetPointerMapping(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_uchar,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetScreenSaver(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetSelectionOwner(
        arg1: *mut Display,
        arg2: Atom,
        arg3: Window,
        arg4: Time,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetState(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_ulong,
        arg4: std::os::raw::c_ulong,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetStipple(arg1: *mut Display, arg2: GC, arg3: Pixmap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetSubwindowMode(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetTSOrigin(
        arg1: *mut Display,
        arg2: GC,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetTile(arg1: *mut Display, arg2: GC, arg3: Pixmap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWindowBackground(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWindowBackgroundPixmap(
        arg1: *mut Display,
        arg2: Window,
        arg3: Pixmap,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWindowBorder(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_ulong,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWindowBorderPixmap(
        arg1: *mut Display,
        arg2: Window,
        arg3: Pixmap,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWindowBorderWidth(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetWindowColormap(
        arg1: *mut Display,
        arg2: Window,
        arg3: Colormap,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XStoreBuffer(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XStoreBytes(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XStoreColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut XColor,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XStoreColors(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut XColor,
        arg4: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XStoreName(
        arg1: *mut Display,
        arg2: Window,
        arg3: *const std::os::raw::c_char,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XStoreNamedColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *const std::os::raw::c_char,
        arg4: std::os::raw::c_ulong,
        arg5: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSync(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XTextExtents(
        arg1: *mut XFontStruct,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut XCharStruct,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XTextExtents16(
        arg1: *mut XFontStruct,
        arg2: *const XChar2b,
        arg3: std::os::raw::c_int,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut XCharStruct,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XTextWidth(
        arg1: *mut XFontStruct,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XTextWidth16(
        arg1: *mut XFontStruct,
        arg2: *const XChar2b,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XTranslateCoordinates(
        arg1: *mut Display,
        arg2: Window,
        arg3: Window,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut Window,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUndefineCursor(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUngrabButton(
        arg1: *mut Display,
        arg2: std::os::raw::c_uint,
        arg3: std::os::raw::c_uint,
        arg4: Window,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUngrabKey(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: std::os::raw::c_uint,
        arg4: Window,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUngrabKeyboard(arg1: *mut Display, arg2: Time) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUngrabPointer(arg1: *mut Display, arg2: Time) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUngrabServer(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUninstallColormap(arg1: *mut Display, arg2: Colormap) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUnloadFont(arg1: *mut Display, arg2: Font) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUnmapSubwindows(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUnmapWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XVendorRelease(arg1: *mut Display) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XWarpPointer(
        arg1: *mut Display,
        arg2: Window,
        arg3: Window,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XWidthMMOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XWidthOfScreen(arg1: *mut Screen) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XWindowEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_long,
        arg4: *mut XEvent,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XWriteBitmapFile(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: Pixmap,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSupportsLocale() -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetLocaleModifiers(arg1: *const std::os::raw::c_char) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XOpenOM(
        arg1: *mut Display,
        arg2: *mut _XrmHashBucketRec,
        arg3: *const std::os::raw::c_char,
        arg4: *const std::os::raw::c_char,
    ) -> XOM;
}
extern "C" {
    pub fn XCloseOM(arg1: XOM) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XSetOMValues(arg1: XOM, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XGetOMValues(arg1: XOM, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XDisplayOfOM(arg1: XOM) -> *mut Display;
}
extern "C" {
    pub fn XLocaleOfOM(arg1: XOM) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XCreateOC(arg1: XOM, ...) -> XOC;
}
extern "C" {
    pub fn XDestroyOC(arg1: XOC);
}
extern "C" {
    pub fn XOMOfOC(arg1: XOC) -> XOM;
}
extern "C" {
    pub fn XSetOCValues(arg1: XOC, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XGetOCValues(arg1: XOC, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XCreateFontSet(
        arg1: *mut Display,
        arg2: *const std::os::raw::c_char,
        arg3: *mut *mut *mut std::os::raw::c_char,
        arg4: *mut std::os::raw::c_int,
        arg5: *mut *mut std::os::raw::c_char,
    ) -> XFontSet;
}
extern "C" {
    pub fn XFreeFontSet(arg1: *mut Display, arg2: XFontSet);
}
extern "C" {
    pub fn XFontsOfFontSet(
        arg1: XFontSet,
        arg2: *mut *mut *mut XFontStruct,
        arg3: *mut *mut *mut std::os::raw::c_char,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XBaseFontNameListOfFontSet(arg1: XFontSet) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XLocaleOfFontSet(arg1: XFontSet) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XContextDependentDrawing(arg1: XFontSet) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XDirectionalDependentDrawing(arg1: XFontSet) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XContextualDrawing(arg1: XFontSet) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XExtentsOfFontSet(arg1: XFontSet) -> *mut XFontSetExtents;
}
extern "C" {
    pub fn XmbTextEscapement(
        arg1: XFontSet,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XwcTextEscapement(
        arg1: XFontSet,
        arg2: *const wchar_t,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn Xutf8TextEscapement(
        arg1: XFontSet,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XmbTextExtents(
        arg1: XFontSet,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut XRectangle,
        arg5: *mut XRectangle,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XwcTextExtents(
        arg1: XFontSet,
        arg2: *const wchar_t,
        arg3: std::os::raw::c_int,
        arg4: *mut XRectangle,
        arg5: *mut XRectangle,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn Xutf8TextExtents(
        arg1: XFontSet,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut XRectangle,
        arg5: *mut XRectangle,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XmbTextPerCharExtents(
        arg1: XFontSet,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut XRectangle,
        arg5: *mut XRectangle,
        arg6: std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut XRectangle,
        arg9: *mut XRectangle,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XwcTextPerCharExtents(
        arg1: XFontSet,
        arg2: *const wchar_t,
        arg3: std::os::raw::c_int,
        arg4: *mut XRectangle,
        arg5: *mut XRectangle,
        arg6: std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut XRectangle,
        arg9: *mut XRectangle,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn Xutf8TextPerCharExtents(
        arg1: XFontSet,
        arg2: *const std::os::raw::c_char,
        arg3: std::os::raw::c_int,
        arg4: *mut XRectangle,
        arg5: *mut XRectangle,
        arg6: std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut XRectangle,
        arg9: *mut XRectangle,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XmbDrawText(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut XmbTextItem,
        arg7: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn XwcDrawText(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut XwcTextItem,
        arg7: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn Xutf8DrawText(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut XmbTextItem,
        arg7: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn XmbDrawString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: XFontSet,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_char,
        arg8: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn XwcDrawString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: XFontSet,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const wchar_t,
        arg8: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn Xutf8DrawString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: XFontSet,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_char,
        arg8: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn XmbDrawImageString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: XFontSet,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_char,
        arg8: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn XwcDrawImageString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: XFontSet,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const wchar_t,
        arg8: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn Xutf8DrawImageString(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: XFontSet,
        arg4: GC,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_char,
        arg8: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn XOpenIM(
        arg1: *mut Display,
        arg2: *mut _XrmHashBucketRec,
        arg3: *mut std::os::raw::c_char,
        arg4: *mut std::os::raw::c_char,
    ) -> XIM;
}
extern "C" {
    pub fn XCloseIM(arg1: XIM) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetIMValues(arg1: XIM, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XSetIMValues(arg1: XIM, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XDisplayOfIM(arg1: XIM) -> *mut Display;
}
extern "C" {
    pub fn XLocaleOfIM(arg1: XIM) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XCreateIC(arg1: XIM, ...) -> XIC;
}
extern "C" {
    pub fn XDestroyIC(arg1: XIC);
}
extern "C" {
    pub fn XSetICFocus(arg1: XIC);
}
extern "C" {
    pub fn XUnsetICFocus(arg1: XIC);
}
extern "C" {
    pub fn XwcResetIC(arg1: XIC) -> *mut wchar_t;
}
extern "C" {
    pub fn XmbResetIC(arg1: XIC) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn Xutf8ResetIC(arg1: XIC) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XSetICValues(arg1: XIC, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XGetICValues(arg1: XIC, ...) -> *mut std::os::raw::c_char;
}
extern "C" {
    pub fn XIMOfIC(arg1: XIC) -> XIM;
}
extern "C" {
    pub fn XFilterEvent(arg1: *mut XEvent, arg2: Window) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XmbLookupString(
        arg1: XIC,
        arg2: *mut XKeyPressedEvent,
        arg3: *mut std::os::raw::c_char,
        arg4: std::os::raw::c_int,
        arg5: *mut KeySym,
        arg6: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XwcLookupString(
        arg1: XIC,
        arg2: *mut XKeyPressedEvent,
        arg3: *mut wchar_t,
        arg4: std::os::raw::c_int,
        arg5: *mut KeySym,
        arg6: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn Xutf8LookupString(
        arg1: XIC,
        arg2: *mut XKeyPressedEvent,
        arg3: *mut std::os::raw::c_char,
        arg4: std::os::raw::c_int,
        arg5: *mut KeySym,
        arg6: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XVaCreateNestedList(arg1: std::os::raw::c_int, ...) -> XVaNestedList;
}
extern "C" {
    pub fn XRegisterIMInstantiateCallback(
        arg1: *mut Display,
        arg2: *mut _XrmHashBucketRec,
        arg3: *mut std::os::raw::c_char,
        arg4: *mut std::os::raw::c_char,
        arg5: XIDProc,
        arg6: XPointer,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XUnregisterIMInstantiateCallback(
        arg1: *mut Display,
        arg2: *mut _XrmHashBucketRec,
        arg3: *mut std::os::raw::c_char,
        arg4: *mut std::os::raw::c_char,
        arg5: XIDProc,
        arg6: XPointer,
    ) -> std::os::raw::c_int;
}
pub type XConnectionWatchProc = ::std::option::Option<
    unsafe extern "C" fn(
        arg1: *mut Display,
        arg2: XPointer,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: *mut XPointer,
    ),
>;
extern "C" {
    pub fn XInternalConnectionNumbers(
        arg1: *mut Display,
        arg2: *mut *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XProcessInternalConnection(arg1: *mut Display, arg2: std::os::raw::c_int);
}
extern "C" {
    pub fn XAddConnectionWatch(
        arg1: *mut Display,
        arg2: XConnectionWatchProc,
        arg3: XPointer,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XRemoveConnectionWatch(arg1: *mut Display, arg2: XConnectionWatchProc, arg3: XPointer);
}
extern "C" {
    pub fn XSetAuthorization(
        arg1: *mut std::os::raw::c_char,
        arg2: std::os::raw::c_int,
        arg3: *mut std::os::raw::c_char,
        arg4: std::os::raw::c_int,
    );
}
extern "C" {
    pub fn _Xmbtowc(
        arg1: *mut wchar_t,
        arg2: *mut std::os::raw::c_char,
        arg3: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
}
extern "C" {
    pub fn _Xwctomb(arg1: *mut std::os::raw::c_char, arg2: wchar_t) -> std::os::raw::c_int;
}
extern "C" {
    pub fn XGetEventData(arg1: *mut Display, arg2: *mut XGenericEventCookie)
        -> std::os::raw::c_int;
}
extern "C" {
    pub fn XFreeEventData(arg1: *mut Display, arg2: *mut XGenericEventCookie);
}

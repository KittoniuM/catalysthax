







typedef HRESULT (WINAPI *tDirectInput8Create)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf,
  LPVOID* ppvOut,  
  LPUNKNOWN punkOuter
);

extern tDirectInput8Create pDirectInput8Create;


HRESULT WINAPI hkDirectInput8Create(
  HINSTANCE hinst, 
  DWORD dwVersion, 
  REFIID riidltf,
  LPVOID* ppvOut,  
  LPUNKNOWN punkOuter
);
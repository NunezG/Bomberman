# Sources

### Passing keyboard events to all players
https://wiki.unrealengine.com/Local_Multiplayer_Tips
Specifically, in [BombermanViewportClient](/Source/Bomberman/Utilities/BombermanViewportCilent.h)
```
virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
```
and in [BombermanViewportCilent.cpp](/Source/Bomberman/Utilities/BombermanViewportCilent.cpp)
```
bool ULocalMPViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (IgnoreInput() || bGamepad || Key.IsMouseButton())
	{
		return Super::InputKey(Viewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);
	}
	else
	{
		// Propagate keyboard events to all players
		UEngine* const Engine = GetOuterUEngine();
		int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
		bool bRetVal = false;
		for (int32 i = 0; i < NumPlayers; i++)
		{
			bRetVal = Super::InputKey(Viewport, i, Key, EventType, AmountDepressed, bGamepad) || bRetVal;
		}
 
		return bRetVal;
	}
}
```
# Sources

### Passing keyboard events to all players
https://wiki.unrealengine.com/Local_Multiplayer_Tips
Specifically, in [BombermanViewportClient](/Source/Bomberman/Utilities/BombermanViewportClient.h)
```
virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
```
and in [BombermanViewportCilent.cpp](/Source/Bomberman/Utilities/BombermanViewportClient.cpp)
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

### File IO (for level loading)
https://answers.unrealengine.com/questions/88289/read-and-write-data-from-text-file.html
Used bits of info from here for my text loading function, though no code has explicitly been directly used.

### Ray tracing (movement, bombs)
http://orfeasel.com/single-line-raycasting/
Used to make the bombs check surrounding tiles while exploding in [BMBomb.cpp](/Source/Bomberman/Gameplay/BMBomb.cpp)
```
AActor* ABMBomb::CalculateBlastHit(FVector direction, FVector & target)
{
	//Calculate hit raytrace
	FHitResult hit;

	//Starting point for the raycast
	FVector startLocation = GetActorLocation();

	//To get the final point of the raycast, we have to multiply the direction of the ray to the travel distance (tileSize), and add it to the start location
	FVector endLocation = startLocation + (direction * blastRange * tileSize);

	//Setup collision parameters to ignore pawn which is casting the ray
	FCollisionQueryParams collisionParameters;
	//collisionParameters.AddIgnoredActor(this);

	//Actual line trace
	GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECollisionChannel::ECC_MAX, collisionParameters);

	//Get the location either from the ray trace or if nothing is hit, then use the max raytrace range
	if(hit.GetActor() == NULL)
	{
		target = startLocation + (direction * blastRange * tileSize);
	}
	else
	{
		target = hit.GetActor()->GetActorLocation();
	}	
	return hit.GetActor();
}
```

### Textures for beam particle
https://wiki.unrealengine.com/Beam_Particle_(Tutorial)

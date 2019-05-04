- provider
	- name			; Will always be "Counter-Strike: Global Offensive"
	- appid			; Will always be 730
	- version		; Current game version number (13512 as of this post) 
	- steamid		; player Steam ID in steamID64 format
	- timestamp		; UNIX time stamp
	

- map
	- name			; map name in typical format (de_dust2, etc.)
	- phase			; "warmup", "live", maybe more?
	- round			; int, current round number
	- team_ct
		- score		; int, current team score
	- team_t
		- score		; int, current team score


- round
	- phase			; "live", "freezetime", "over" (maybe "warmup", others?)
	- bomb			; "planted", "exploded", or "defused"
	- win_team		; "CT" or "T"


- player_id
	- steamid			; steamid in steamID64 format
	- name				; current in-game name
	- activity			; "menu", "playing", "textinput" (console)
	- team				; "CT" or "T"

	
- player_state
	- player
		- state
			- health		; int, 0-100, current HP
			- armor			; int, 0-100, current armor
			- helmet		; bool, true/false if they have helm armor
			- flashed		; int, 0-255 depending on how flashed the player is
			- smoked		; same as above, but for smoke
			- burning		; same as above, but for fire
			- money			; current money
			- round_kills	; how many kills the player got in that round
			- round_killhs	; how many headshot kills the player got (hs kills increase this *and* the above's number)
			

- player_weapons
	- player
		- weapons
			- weapon_0 (_1, _2, _3, etc.)
				- name			; weapon name
				- paintkit		; appears to be an internally used skin name, or "default" if none
				- type			; "Knife", "Pistol", "Submachine Gun", etc. 
				- state			; "holstered" or "active"
				- ammo_clip		; int, amount of current ammo in clip
				- ammo_clip_max	; int, max amount of ammo a clip can hold
				- ammo_reserve	; int, amount of reserve ammo, not in clip
				
				
- player_match_stats
	- player
		- match_stats
			- kills			; int, total kills
			- assists		; int, total assists
			- deaths		; int, total deaths
			- mvps			; int, number of MVPs
			- score			; int, current score

# Example payload

55;25;1000;10;10;1;1;1

55;25;1000;0;10;1;1;1


VEHICLES = {}
function VehiclesAddToTable(name,hash,codename,class,fullname,maker)
	VEHICLES[name] = {
		Hash = hash,
		Codename = codename,
		Class = class,
		FullName = fullname,
		Maker = maker
	}
	VEHICLES[hash] = name
end

VehiclesAddToTable("ADDER",0xB779A091,"ADDER","Super","Adder","Truffade")
VehiclesAddToTable("AIRBUS",0x4C80EB0E,"AIRBUS","Service","Airport Bus","")
VehiclesAddToTable("AIRTUG",0x5D0AAC8F,"AIRTUG","Utility","Airtug","")
VehiclesAddToTable("AKUMA",0x63ABADE7,"AKUMA","Motorcycles","Akuma","Dinka")
VehiclesAddToTable("ALPHA",0x2DB8D1AA,"ALPHA","Sports","Alpha","Albany")
VehiclesAddToTable("AMBULANCE",0x45D56ADA,"AMBULAN","Emergency","Ambulance","")
VehiclesAddToTable("ANNIHILATOR",0x31F0B376,"ANNIHL","Helicopters","Annihilator","")
VehiclesAddToTable("ARMYTANKER",0xB8081009,"ARMYTRAILER","Utility","Army Trailer","")
VehiclesAddToTable("ARMYTRAILER",0xA7FF33F5,"ARMYTRAILER","Utility","Army Trailer","")
VehiclesAddToTable("ARMYTRAILER2",0x9E6B14D6,"ARMYTRAILER","Utility","Army Trailer","")
VehiclesAddToTable("ASEA",0x94204D89,"ASEA","SUVs","Asea","Declasse")
VehiclesAddToTable("ASEA2",0x9441D8D5,"ASEA","SUVs","Asea","Declasse")
VehiclesAddToTable("ASTEROPE",0x8E9254FB,"ASTROPE","SUVs","Asterope","Karin")
VehiclesAddToTable("BAGGER",0x806B9CC3,"BAGGER","Motorcycles","Bagger","Western")
VehiclesAddToTable("BALETRAILER",0xE82AE656,"BALETRAILER","Utility","Baletrailer","")
VehiclesAddToTable("BALLER",0xCFCA3668,"BALLER","Sedans","Baller","Gallivanter")
VehiclesAddToTable("BALLER2",0x8852855,"BALLER2","Sedans","Baller","Gallivanter")
VehiclesAddToTable("BALLER3",0x6FF0F727,"BALLER3","Sedans","Baller LE","Gallivanter")
VehiclesAddToTable("BALLER4",0x25CBE2E2,"BALLER4","Sedans","Baller LE LWB","Gallivanter")
VehiclesAddToTable("BALLER5",0x1C09CF5E,"BALLER5","Sedans","Baller LE (Armored)","Gallivanter")
VehiclesAddToTable("BALLER6",0x27B4E6B0,"BALLER6","Sedans","Baller LE LWB (Armored)","Gallivanter")
VehiclesAddToTable("BANSHEE",0xC1E908D2,"BANSHEE","Sports","Banshee","Bravado")
VehiclesAddToTable("BARRACKS",0xCEEA3F4B,"BARRACKS","Military","Barracks","")
VehiclesAddToTable("BARRACKS2",0x4008EABB,"BARRACKS2","Military","Barracks Semi","HVY")
VehiclesAddToTable("BARRACKS3",0x2592B5CF,"BARRACKS","Military","Barracks","")
VehiclesAddToTable("BATI",0xF9300CC5,"BATI","Motorcycles","Bati 801","Pegassi")
VehiclesAddToTable("BATI2",0xCADD5D2D,"BATI2","Motorcycles","Bati 801RR","Pegassi")
VehiclesAddToTable("BENSON",0x7A61B330,"BENSON","Commercial","Benson","Vapid")
VehiclesAddToTable("BESRA",0x6CBD1D6D,"BESRA","Airplanes","Besra","Western")
VehiclesAddToTable("BFINJECTION",0x432AA566,"BFINJECT","Off-Road","Injection","BF")
VehiclesAddToTable("BIFF",0x32B91AE8,"BIFF","Commercial","Biff","HVY")
VehiclesAddToTable("BIFTA",0xEB298297,"BIFTA","Off-Road","Bifta","BF")
VehiclesAddToTable("BISON",0xFEFD644F,"BISON","Vans/Pickups","Bison","Bravado")
VehiclesAddToTable("BISON2",0x7B8297C5,"BISON","Vans/Pickups","Bison","Bravado")
VehiclesAddToTable("BISON3",0x67B3F020,"BISON","Vans/Pickups","Bison","Bravado")
VehiclesAddToTable("BJXL",0x32B29A4B,"BJXL","Sedans","BeeJay XL","Karin")
VehiclesAddToTable("BLADE",0xB820ED5E,"BLADE","Muscle","Blade","Vapid")
VehiclesAddToTable("BLAZER",0x8125BCF9,"BLAZER","Off-Road","Blazer","Nagasaki")
VehiclesAddToTable("BLAZER2",0xFD231729,"BLAZER2","Off-Road","Blazer Lifeguard","Nagasaki")
VehiclesAddToTable("BLAZER3",0xB44F0582,"BLAZER03","Off-Road","Hot Rod Blazer","Nagasaki")
VehiclesAddToTable("BLIMP",0xF7004C86,"BLIMP","Airplanes","Atomic Blimp","")
VehiclesAddToTable("BLIMP2",0xDB6B4924,"BLIMP2","Airplanes","Xero Blimp","")
VehiclesAddToTable("BLISTA",0xEB70965F,"BLISTA","Compacts","Blista","Dinka")
VehiclesAddToTable("BLISTA2",0x3DEE5EDA,"BLISTA2","Sports","Blista Compact","Dinka")
VehiclesAddToTable("BLISTA3",0xDCBC1C3B,"BLISTA3","Sports","Go Go Monkey Blista","Dinka")
VehiclesAddToTable("BMX",0x43779C54,"BMX","Bicycles","BMX","")
VehiclesAddToTable("BOATTRAILER",0x1F3D44B5,"BOATTRAILER","Utility","Boat Trailer","")
VehiclesAddToTable("BOBCATXL",0x3FC5D440,"BOBCATXL","Vans/Pickups","Bobcat XL","Vapid")
VehiclesAddToTable("BODHI2",0xAA699BB6,"BODHI2","Off-Road","Bodhi","Canis")
VehiclesAddToTable("BOXVILLE",0x898ECCEA,"BOXVILLE","Vans/Pickups","Boxville","")
VehiclesAddToTable("BOXVILLE2",0xF21B33BE,"BOXVILLE","Vans/Pickups","Boxville","")
VehiclesAddToTable("BOXVILLE3",0x7405E08,"BOXVILLE","Vans/Pickups","Boxville","Brute")
VehiclesAddToTable("BOXVILLE4",0x1A79847A,"BOXVILLE","Vans/Pickups","Boxville","Brute")
VehiclesAddToTable("BRAWLER",0xA7CE1BC5,"BRAWLER","Off-Road","Brawler","Coil")
VehiclesAddToTable("BTYPE",0x6FF6914,"ROOSEVELT","Sports Classics","Roosevelt","Albany")
VehiclesAddToTable("BTYPE2",0xCE6B35A4,"BTYPE2","Sports Classics","Fränken Stange","Albany")
VehiclesAddToTable("BUCCANEER",0xD756460C,"BUCCANEE","Muscle","Buccaneer","Albany")
VehiclesAddToTable("BUCCANEER2",0xC397F748,"BUCCANEE2","Muscle","Buccaneer Custom","Albany")
VehiclesAddToTable("BUFFALO",0xEDD516C6,"BUFFALO","Sports","Buffalo","Bravado")
VehiclesAddToTable("BUFFALO2",0x2BEC3CBE,"BUFFALO02","Sports","Buffalo S","Bravado")
VehiclesAddToTable("BUFFALO3",0xE2C013E,"BUFFALO3","Sports","Sprunk Buffalo","Bravado")
VehiclesAddToTable("BULLDOZER",0x7074F39D,"BULLDOZE","Industrial","Dozer","HVY")
VehiclesAddToTable("BULLET",0x9AE6DDA1,"BULLET","Super","Bullet","Vapid")
VehiclesAddToTable("BURRITO",0xAFBB2CA4,"BURRITO","Vans/Pickups","Burrito","Declasse")
VehiclesAddToTable("BURRITO2",0xC9E8FF76,"BURRITO","Vans/Pickups","Burrito","Declasse")
VehiclesAddToTable("BURRITO3",0x98171BD3,"BURRITO","Vans/Pickups","Burrito","Declasse")
VehiclesAddToTable("BURRITO4",0x353B561D,"BURRITO","Vans/Pickups","Burrito","Declasse")
VehiclesAddToTable("BURRITO5",0x437CF2A0,"BURRITO","Vans/Pickups","Burrito","Declasse")
VehiclesAddToTable("BUS",0xD577C962,"BUS","Service","Bus","")
VehiclesAddToTable("BUZZARD",0x2F03547B,"BUZZARD","Helicopters","Buzzard Attack Chopper","")
VehiclesAddToTable("BUZZARD2",0x2C75F0DD,"BUZZARD2","Helicopters","Buzzard","")
VehiclesAddToTable("CABLECAR",0xC6C3242D,"CABLECAR","Trains","Cable Car","")
VehiclesAddToTable("CADDY",0x44623884,"CADDY","Utility","Caddy","")
VehiclesAddToTable("CADDY2",0xDFF0594C,"CADDY","Utility","Caddy","")
VehiclesAddToTable("CAMPER",0x6FD95F68,"CAMPER","Vans/Pickups","Camper","Brute")
VehiclesAddToTable("CARBONIZZARE",0x7B8AB45F,"CARBONIZ","Sports","Carbonizzare","Grotti")
VehiclesAddToTable("CARBONRS",0xABB0C0,"CARBON","Motorcycles","Carbon RS","Nagasaki")
VehiclesAddToTable("CARGOBOB",0xFCFCB68B,"CARGOBOB","Helicopters","Cargobob","")
VehiclesAddToTable("CARGOBOB2",0x60A7EA10,"CARGOBOB","Helicopters","Cargobob","")
VehiclesAddToTable("CARGOBOB3",0x53174EEF,"CARGOBOB","Helicopters","Cargobob","")
VehiclesAddToTable("CARGOBOB4",0x78BC1A3C,"CARGOBOB","Helicopters","Cargobob","")
VehiclesAddToTable("CARGOPLANE",0x15F27762,"CARGOPL","Airplanes","Cargo Plane","")
VehiclesAddToTable("CASCO",0x3822BDFE,"CASCO","Sports Classics","Casco","Lampadati")
VehiclesAddToTable("CAVALCADE",0x779F23AA,"CAVCADE","Sedans","Cavalcade","Albany")
VehiclesAddToTable("CAVALCADE2",0xD0EB2BE5,"CAVCADE","Sedans","Cavalcade","Albany")
VehiclesAddToTable("CHEETAH",0xB1D95DA0,"CHEETAH","Super","Cheetah","Grotti")
VehiclesAddToTable("CHINO",0x14D69010,"CHINO","Muscle","Chino","Vapid")
VehiclesAddToTable("CHINO2",0xAED64A63,"CHINO2","Muscle","Chino Custom","Vapid")
VehiclesAddToTable("COACH",0x84718D34,"COACH","Service","Dashound","")
VehiclesAddToTable("COG55",0x360A438E,"COG55","SUVs","Cognoscenti 55","Enus")
VehiclesAddToTable("COG552",0x29FCD3E4,"COG552","SUVs","Cognoscenti 55 (Armored)","Enus")
VehiclesAddToTable("COGCABRIO",0x13B57D8A,"COGCABRI","Coupes","Cognoscenti Cabrio","Enus")
VehiclesAddToTable("COGNOSCENTI",0x86FE0B60,"COGNOSC","SUVs","Cognoscenti","Enus")
VehiclesAddToTable("COGNOSCENTI2",0xDBF2D57A,"COGNOSC2","SUVs","Cognoscenti (Armored)","Enus")
VehiclesAddToTable("COMET2",0xC1AE4D16,"COMET2","Sports","Comet","Pfister")
VehiclesAddToTable("COQUETTE",0x67BC037,"COQUETTE","Sports","Coquette","Invetero")
VehiclesAddToTable("COQUETTE2",0x3C4E2113,"COQUETTE2","Sports Classics","Coquette Classic","Invetero")
VehiclesAddToTable("COQUETTE3",0x2EC385FE,"COQUETTE3","Muscle","Coquette BlackFin","Invetero")
VehiclesAddToTable("CRUISER",0x1ABA13B5,"CRUISER","Bicycles","Cruiser","")
VehiclesAddToTable("CRUSADER",0x132D5A1A,"CRUSADER","Military","Crusader","Canis")
VehiclesAddToTable("CUBAN800",0xD9927FE3,"CUBAN800","Airplanes","Cuban 800","")
VehiclesAddToTable("CUTTER",0xC3FBA120,"CUTTER","Industrial","Cutter","HVY")
VehiclesAddToTable("DAEMON",0x77934CEE,"DAEMON","Motorcycles","Daemon","Western")
VehiclesAddToTable("DILETTANTE",0xBC993509,"DILETTAN","Compacts","Dilettante","Karin")
VehiclesAddToTable("DILETTANTE2",0x64430650,"DILETTAN","Compacts","Dilettante","Karin")
VehiclesAddToTable("DINGHY",0x3D961290,"DINGHY","Boats","Dinghy","Nagasaki")
VehiclesAddToTable("DINGHY2",0x107F392C,"DINGHY","Boats","Dinghy","Nagasaki")
VehiclesAddToTable("DINGHY3",0x1E5E54EA,"DINGHY","Boats","Dinghy","Nagasaki")
VehiclesAddToTable("DINGHY4",0x33B47F96,"DINGHY","Boats","Dinghy","Nagasaki")
VehiclesAddToTable("DLOADER",0x698521E3,"DLOADER","Off-Road","Duneloader","Bravado")
VehiclesAddToTable("DOCKTRAILER",0x806EFBEE,"DOCKTRAILER","Utility","NULL","")
VehiclesAddToTable("DOCKTUG",0xCB44B1CA,"DOCKTUG","Utility","Docktug","")
VehiclesAddToTable("DODO",0xCA495705,"DODO","Airplanes","Dodo","Mammoth")
VehiclesAddToTable("DOMINATOR",0x4CE68AC,"DOMINATO","Muscle","Dominator","Vapid")
VehiclesAddToTable("DOMINATOR2",0xC96B73D9,"DOMINATO2","Muscle","Pisswasser Dominator","Vapid")
VehiclesAddToTable("DOUBLE",0x9C669788,"DOUBLE","Motorcycles","Double-T","Dinka")
VehiclesAddToTable("DUBSTA",0x462FE277,"DUBSTA","Sedans","Dubsta","Benefactor")
VehiclesAddToTable("DUBSTA2",0xE882E5F6,"DUBSTA","Sedans","Dubsta","Benefactor")
VehiclesAddToTable("DUBSTA3",0xB6410173,"DUBSTA3","Off-Road","Dubsta 6x6","Benefactor")
VehiclesAddToTable("DUKES",0x2B26F456,"DUKES","Muscle","Dukes","Imponte")
VehiclesAddToTable("DUKES2",0xEC8F7094,"DUKES2","Muscle","Duke O'Death","Imponte")
VehiclesAddToTable("DUMP",0x810369E2,"DUMP","Industrial","Dump","HVY")
VehiclesAddToTable("DUNE",0x9CF21E0F,"DUNE","Off-Road","Dune Buggy","BF")
VehiclesAddToTable("DUNE2",0x1FD824AF,"DUNE2","Off-Road","Space Docker","")
VehiclesAddToTable("DUSTER",0x39D6779E,"DUSTER","Airplanes","Duster","")
VehiclesAddToTable("ELEGY2",0xDE3D9D22,"ELEGY2","Sports","Elegy RH8","Annis")
VehiclesAddToTable("EMPEROR",0xD7278283,"EMPEROR","SUVs","Emperor","Albany")
VehiclesAddToTable("EMPEROR2",0x8FC3AADC,"EMPEROR","SUVs","Emperor","Albany")
VehiclesAddToTable("EMPEROR3",0xB5FCF74E,"EMPEROR","SUVs","Emperor","Albany")
VehiclesAddToTable("ENDURO",0x6882FA73,"ENDURO","Motorcycles","Enduro","Dinka")
VehiclesAddToTable("ENTITYXF",0xB2FE5CF9,"ENTITYXF","Super","Entity XF","Overflod")
VehiclesAddToTable("EXEMPLAR",0xFFB15B5E,"EXEMPLAR","Coupes","Exemplar","Dewbauchee")
VehiclesAddToTable("F620",0xDCBCBE48,"F620","Coupes","F620","Ocelot")
VehiclesAddToTable("FACTION",0x81A9CDDF,"FACTION","Muscle","Faction","Willard")
VehiclesAddToTable("FACTION2",0x95466BDB,"FACTION2","Muscle","Faction Custom","Willard")
VehiclesAddToTable("FAGGIO2",0x350D1AB,"FAGGIO","Motorcycles","Faggio","Pegassi")
VehiclesAddToTable("FBI",0x432EA949,"FBI","Emergency","FIB","")
VehiclesAddToTable("FBI2",0x9DC66994,"FBI2","Emergency","FIB","")
VehiclesAddToTable("FELON",0xE8A8BDA8,"FELON","Coupes","Felon","Lampadati")
VehiclesAddToTable("FELON2",0xFAAD85EE,"FELON2","Coupes","Felon GT","Lampadati")
VehiclesAddToTable("FELTZER2",0x8911B9F5,"FELTZER","Sports","Feltzer","Benefactor")
VehiclesAddToTable("FELTZER3",0xA29D6D10,"FELTZER3","Sports Classics","Stirling GT","Benefactor")
VehiclesAddToTable("FIRETRUK",0x73920F8E,"FIRETRUK","Emergency","Fire Truck","")
VehiclesAddToTable("FIXTER",0xCE23D3BF,"FIXTER","Bicycles","Fixter","")
VehiclesAddToTable("FLATBED",0x50B0215A,"FLATBED","Industrial","Flatbed","MTL")
VehiclesAddToTable("FORKLIFT",0x58E49664,"FORK","Utility","Forklift","HVY")
VehiclesAddToTable("FQ2",0xBC32A33B,"FQ2","Sedans","FQ 2","Fathom")
VehiclesAddToTable("FREIGHT",0x3D6AAA9B,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("FREIGHTCAR",0xAFD22A6,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("FREIGHTCONT1",0x36DCFF98,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("FREIGHTCONT2",0xE512E79,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("FREIGHTGRAIN",0x264D9262,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("FREIGHTTRAILER",0xD1ABB666,"FREIGHTTRAILER","Utility","NULL","")
VehiclesAddToTable("FROGGER",0x2C634FBD,"FROGGER","Helicopters","Frogger","")
VehiclesAddToTable("FROGGER2",0x742E9AC0,"FROGGER","Helicopters","Frogger","")
VehiclesAddToTable("FUGITIVE",0x71CB2FFB,"FUGITIVE","SUVs","Fugitive","Cheval")
VehiclesAddToTable("FUROREGT",0xBF1691E0,"FURORE","Sports","Furore GT","Lampadati")
VehiclesAddToTable("FUSILADE",0x1DC0BA53,"FUSILADE","Sports","Fusilade","Schyster")
VehiclesAddToTable("FUTO",0x7836CE2F,"FUTO","Sports","Futo","Karin")
VehiclesAddToTable("GAUNTLET",0x94B395C5,"GAUNTLET","Muscle","Gauntlet","Bravado")
VehiclesAddToTable("GAUNTLET2",0x14D22159,"GAUNTLET2","Muscle","Redwood Gauntlet","Bravado")
VehiclesAddToTable("GBURRITO",0x97FA4F36,"GBURRITO","Vans/Pickups","Gang Burrito","Declasse")
VehiclesAddToTable("GBURRITO2",0x11AA0E14,"GBURRITO2","Vans/Pickups","Gang Burrito","Declasse")
VehiclesAddToTable("GLENDALE",0x47A6BC1,"GLENDALE","SUVs","Glendale","Benefactor")
VehiclesAddToTable("GRAINTRAILER",0x3CC7F596,"GRAINTRAILER","Utility","Graintrailer","")
VehiclesAddToTable("GRANGER",0x9628879C,"GRANGER","Sedans","Granger","Declasse")
VehiclesAddToTable("GRESLEY",0xA3FC0F4D,"GRESLEY","Sedans","Gresley","Bravado")
VehiclesAddToTable("GUARDIAN",0x825A9F4C,"GUARDIAN","Industrial","Guardian","Vapid")
VehiclesAddToTable("HABANERO",0x34B7390F,"HABANERO","Sedans","Habanero","Emperor")
VehiclesAddToTable("HAKUCHOU",0x4B6C568A,"HAKUCHOU","Motorcycles","Hakuchou","Shitzu")
VehiclesAddToTable("HANDLER",0x1A7FCEFA,"HANDLER","Industrial","Dock Handler","")
VehiclesAddToTable("HAULER",0x5A82F9AE,"HAULER","Commercial","Hauler","Jobuilt")
VehiclesAddToTable("HEXER",0x11F76C14,"HEXER","Motorcycles","Hexer","LCC")
VehiclesAddToTable("HOTKNIFE",0x239E390,"HOTKNIFE","Muscle","Hotknife","Vapid")
VehiclesAddToTable("HUNTLEY",0x1D06D681,"HUNTLEY","Sedans","Huntley S","Enus")
VehiclesAddToTable("HYDRA",0x39D6E83F,"HYDRA","Airplanes","Hydra","Mammoth")
VehiclesAddToTable("INFERNUS",0x18F25AC7,"INFERNUS","Super","Infernus","Pegassi")
VehiclesAddToTable("INGOT",0xB3206692,"INGOT","SUVs","Ingot","Vulcar")
VehiclesAddToTable("INNOVATION",0xF683EACA,"INNOVATION","Motorcycles","Innovation","LCC")
VehiclesAddToTable("INSURGENT",0x9114EADA,"INSURGENT","Off-Road","Insurgent Pick-Up","HVY")
VehiclesAddToTable("INSURGENT2",0x7B7E56F0,"INSURGENT2","Off-Road","Insurgent","HVY")
VehiclesAddToTable("INTRUDER",0x34DD8AA1,"INTRUDER","SUVs","Intruder","Karin")
VehiclesAddToTable("ISSI2",0xB9CB3B69,"ISSI2","Compacts","Issi","Weeny")
VehiclesAddToTable("JACKAL",0xDAC67112,"JACKAL","Coupes","Jackal","Ocelot")
VehiclesAddToTable("JB700",0x3EAB5555,"JB700","Sports Classics","JB 700","Dewbauchee")
VehiclesAddToTable("JESTER",0xB2A716A3,"JESTER","Sports","Jester","Dinka")
VehiclesAddToTable("JESTER2",0xBE0E6126,"JESTER2","Sports","Jester (Racecar)","Dinka")
VehiclesAddToTable("JET",0x3F119114,"JET","Airplanes","Jet","")
VehiclesAddToTable("JETMAX",0x33581161,"JETMAX","Boats","Jetmax","Shitzu")
VehiclesAddToTable("JOURNEY",0xF8D48E7A,"JOURNEY","Vans/Pickups","Journey","Zirconium")
VehiclesAddToTable("KALAHARI",0x5852838,"KALAHARI","Off-Road","Kalahari","Canis")
VehiclesAddToTable("KHAMELION",0x206D1B68,"KHAMEL","Sports","Khamelion","Hijak")
VehiclesAddToTable("KURUMA",0xAE2BFE94,"KURUMA","Sports","Kuruma","Karin")
VehiclesAddToTable("KURUMA2",0x187D938D,"KURUMA2","Sports","Kuruma (Armored)","Karin")
VehiclesAddToTable("LANDSTALKER",0x4BA4E8DC,"LANDSTAL","Sedans","Landstalker","Dundreary")
VehiclesAddToTable("LAZER",0xB39B0AE6,"LAZER","Airplanes","P-996 LAZER","")
VehiclesAddToTable("LECTRO",0x26321E67,"LECTRO","Motorcycles","Lectro","Principe")
VehiclesAddToTable("LGUARD",0x1BF8D381,"LGUARD","Emergency","Lifeguard","")
VehiclesAddToTable("LIMO2",0xF92AEC4D,"LIMO2","SUVs","Turreted Limo","Benefactor")
VehiclesAddToTable("LURCHER",0x7B47A6A7,"LURCHER","Muscle","Lurcher","Albany")
VehiclesAddToTable("LUXOR",0x250B0C5E,"LUXOR","Airplanes","Luxor","Buckingham")
VehiclesAddToTable("LUXOR2",0xB79F589E,"LUXOR2","Airplanes","Luxor Deluxe","Buckingham")
VehiclesAddToTable("MAMBA",0x9CFFFC56,"MAMBA","Sports Classics","Mamba","Declasse")
VehiclesAddToTable("MAMMATUS",0x97E55D11,"MAMMATUS","Airplanes","Mammatus","")
VehiclesAddToTable("MANANA",0x81634188,"MANANA","Sports Classics","Manana","Albany")
VehiclesAddToTable("MARQUIS",0xC1CE1183,"MARQUIS","Boats","Marquis","Dinka")
VehiclesAddToTable("MARSHALL",0x49863E9C,"MARSHALL","Off-Road","Marshall","Cheval")
VehiclesAddToTable("MASSACRO",0xF77ADE32,"MASSACRO","Sports","Massacro","Dewbauchee")
VehiclesAddToTable("MASSACRO2",0xDA5819A3,"MASSACRO2","Sports","Massacro (Racecar)","Dewbauchee")
VehiclesAddToTable("MAVERICK",0x9D0450CA,"MAVERICK","Helicopters","Maverick","")
VehiclesAddToTable("MESA",0x36848602,"MESA","Sedans","Mesa","Canis")
VehiclesAddToTable("MESA2",0xD36A4B44,"MESA","Sedans","Mesa","Canis")
VehiclesAddToTable("MESA3",0x84F42E51,"MESA","Off-Road","Mesa","Canis")
VehiclesAddToTable("METROTRAIN",0x33C9E158,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("MILJET",0x9D80F93,"MILJET","Airplanes","Miljet","Buckingham")
VehiclesAddToTable("MINIVAN",0xED7EADA4,"MINIVAN","Vans/Pickups","Minivan","Vapid")
VehiclesAddToTable("MIXER",0xD138A6BB,"MIXER","Industrial","Mixer","HVY")
VehiclesAddToTable("MIXER2",0x1C534995,"MIXER2","Industrial","Mixer","HVY")
VehiclesAddToTable("MONROE",0xE62B361B,"MONROE","Sports Classics","Monroe","Pegassi")
VehiclesAddToTable("MONSTER",0xCD93A7DB,"MONSTER","Off-Road","Liberator","Vapid")
VehiclesAddToTable("MOONBEAM",0x1F52A43F,"MOONBEAM","Muscle","Moonbeam","Declasse")
VehiclesAddToTable("MOONBEAM2",0x710A2B9B,"MOONBEAM2","Muscle","Moonbeam Custom","Declasse")
VehiclesAddToTable("MOWER",0x6A4BD8F6,"MOWER","Utility","Lawn Mower","")
VehiclesAddToTable("MULE",0x35ED670B,"MULE","Commercial","Mule","Maibatsu")
VehiclesAddToTable("MULE2",0xC1632BEB,"MULE","Commercial","Mule","Maibatsu")
VehiclesAddToTable("MULE3",0x85A5B471,"MULE","Commercial","Mule","Maibatsu")
VehiclesAddToTable("NEMESIS",0xDA288376,"NEMESIS","Motorcycles","Nemesis","Principe")
VehiclesAddToTable("NIGHTSHADE",0x8C2BD0DC,"NITESHAD","Muscle","Nightshade","Imponte")
VehiclesAddToTable("NINEF",0x3D8FA25C,"NINEF","Sports","9F","Obey")
VehiclesAddToTable("NINEF2",0xA8E38B01,"NINEF2","Sports","9F Cabrio","Obey")
VehiclesAddToTable("ORACLE",0x506434F6,"ORACLE2","Coupes","Oracle XS","Ubermacht")
VehiclesAddToTable("ORACLE2",0xE18195B2,"ORACLE","Coupes","Oracle","Ubermacht")
VehiclesAddToTable("OSIRIS",0x767164D6,"OSIRIS","Super","Osiris","Pegassi")
VehiclesAddToTable("PACKER",0x21EEE87D,"PACKER","Commercial","Packer","MTL")
VehiclesAddToTable("PANTO",0xE644E480,"PANTO","Compacts","Panto","Benefactor")
VehiclesAddToTable("PARADISE",0x58B3979C,"PARADISE","Vans/Pickups","Paradise","Bravado")
VehiclesAddToTable("PATRIOT",0xCFCFEB3B,"PATRIOT","Sedans","Patriot","Mammoth")
VehiclesAddToTable("PBUS",0x885F3671,"PBUS","Emergency","Prison Bus","")
VehiclesAddToTable("PCJ",0xC9CEAF06,"PCJ","Motorcycles","PCJ 600","Shitzu")
VehiclesAddToTable("PENUMBRA",0xE9805550,"PENUMBRA","Sports","Penumbra","Maibatsu")
VehiclesAddToTable("PEYOTE",0x6D19CCBC,"PEYOTE","Sports Classics","Peyote","Vapid")
VehiclesAddToTable("PHANTOM",0x809AA4CB,"PHANTOM","Commercial","Phantom","Jobuilt")
VehiclesAddToTable("PHOENIX",0x831A21D5,"PHOENIX","Muscle","Phoenix","Imponte")
VehiclesAddToTable("PICADOR",0x59E0FBF3,"PICADOR","Muscle","Picador","Cheval")
VehiclesAddToTable("PIGALLE",0x404B6381,"PIGALLE","Sports Classics","Pigalle","Lampadati")
VehiclesAddToTable("POLICE",0x79FBB0C5,"POLICE","Emergency","Police Cruiser","")
VehiclesAddToTable("POLICE2",0x9F05F101,"POLICE2","Emergency","Police Cruiser","")
VehiclesAddToTable("POLICE3",0x71FA16EA,"POLICE","Emergency","Police Cruiser","")
VehiclesAddToTable("POLICE4",0x8A63C7B9,"POLICE4","Emergency","Unmarked Cruiser","")
VehiclesAddToTable("POLICEB",0xFDEFAEC3,"POLICEB","Emergency","Police Bike","")
VehiclesAddToTable("POLICEOLD1",0xA46462F7,"POLICEO1","Emergency","Police Rancher","")
VehiclesAddToTable("POLICEOLD2",0x95F4C618,"POLICEO2","Emergency","Police Roadcruiser","")
VehiclesAddToTable("POLICET",0x1B38E955,"POLICET","Emergency","Police Transporter","")
VehiclesAddToTable("POLMAV",0x1517D4D9,"POLMAV","Helicopters","Police Maverick","")
VehiclesAddToTable("PONY",0xF8DE29A8,"PONY","Vans/Pickups","Pony","Brute")
VehiclesAddToTable("PONY2",0x38408341,"PONY","Vans/Pickups","Pony","Brute")
VehiclesAddToTable("POUNDER",0x7DE35E7D,"POUNDER","Commercial","Pounder","MTL")
VehiclesAddToTable("PRAIRIE",0xA988D3A2,"PRAIRIE","Compacts","Prairie","Bollokan")
VehiclesAddToTable("PRANGER",0x2C33B46E,"PRANGER","Emergency","Park Ranger","")
VehiclesAddToTable("PREDATOR",0xE2E7D4AB,"PREDATOR","Boats","Police Predator","")
VehiclesAddToTable("PREMIER",0x8FB66F9B,"PREMIER","SUVs","Premier","Declasse")
VehiclesAddToTable("PRIMO",0xBB6B404F,"PRIMO","SUVs","Primo","Albany")
VehiclesAddToTable("PRIMO2",0x86618EDA,"PRIMO2","SUVs","Primo Custom","Albany")
VehiclesAddToTable("PROPTRAILER",0x153E1B0A,"PROPTRAILER","Utility","NULL","")
VehiclesAddToTable("RADI",0x9D96B45B,"RADI","Sedans","Radius","Vapid")
VehiclesAddToTable("RAKETRAILER",0x174CB172,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("RANCHERXL",0x6210CBB0,"RANCHERX","Off-Road","Rancher XL","Declasse")
VehiclesAddToTable("RANCHERXL2",0x7341576B,"RANCHERX","Off-Road","Rancher XL","Declasse")
VehiclesAddToTable("RAPIDGT",0x8CB29A14,"RAPIDGT","Sports","Rapid GT","Dewbauchee")
VehiclesAddToTable("RAPIDGT2",0x679450AF,"RAPIDGT","Sports","Rapid GT","Dewbauchee")
VehiclesAddToTable("RATLOADER",0xD83C13CE,"RLOADER","Muscle","Rat-Loader","")
VehiclesAddToTable("RATLOADER2",0xDCE1D9F7,"RLOADER2","Muscle","Rat-Truck","Bravado")
VehiclesAddToTable("REBEL",0xB802DD46,"REBEL01","Off-Road","Rusty Rebel","Karin")
VehiclesAddToTable("REBEL2",0x8612B64B,"REBEL02","Off-Road","Rebel","Karin")
VehiclesAddToTable("REGINA",0xFF22D208,"REGINA","SUVs","Regina","Dundreary")
VehiclesAddToTable("RENTALBUS",0xBE819C63,"RENTBUS","Service","Rental Shuttle Bus","")
VehiclesAddToTable("RHAPSODY",0x322CF98F,"RHAPSODY","Compacts","Rhapsody","Declasse")
VehiclesAddToTable("RHINO",0x2EA68690,"RHINO","Military","Rhino Tank","")
VehiclesAddToTable("RIOT",0xB822A1AA,"RIOT","Emergency","Police Riot","")
VehiclesAddToTable("RIPLEY",0xCD935EF9,"RIPLEY","Utility","Ripley","")
VehiclesAddToTable("ROCOTO",0x7F5C91F1,"ROCOTO","Sedans","Rocoto","Obey")
VehiclesAddToTable("ROMERO",0x2560B2FC,"ROMERO","SUVs","Romero Hearse","Chariot")
VehiclesAddToTable("RUBBLE",0x9A5B1DCC,"RUBBLE","Industrial","Rubble","Jobuilt")
VehiclesAddToTable("RUFFIAN",0xCABD11E8,"RUFFIAN","Motorcycles","Ruffian","Pegassi")
VehiclesAddToTable("RUINER",0xF26CEFF9,"RUINER","Muscle","Ruiner","Imponte")
VehiclesAddToTable("RUMPO",0x4543B74D,"RUMPO","Vans/Pickups","Rumpo","Bravado")
VehiclesAddToTable("RUMPO2",0x961AFEF7,"RUMPO","Vans/Pickups","Rumpo","Bravado")
VehiclesAddToTable("SABREGT",0x9B909C94,"SABREGT","Muscle","Sabre Turbo","Declasse")
VehiclesAddToTable("SADLER",0xDC434E51,"SADLER","Utility","Sadler","Vapid")
VehiclesAddToTable("SADLER2",0x2BC345D1,"SADLER","Utility","Sadler","Vapid")
VehiclesAddToTable("SANCHEZ",0x2EF89E46,"SANCHEZ01","Motorcycles","Sanchez (livery)","Maibatsu")
VehiclesAddToTable("SANCHEZ2",0xA960B13E,"SANCHEZ02","Motorcycles","Sanchez","Maibatsu")
VehiclesAddToTable("SANDKING",0xB9210FD0,"SANDKING","Off-Road","Sandking XL","Vapid")
VehiclesAddToTable("SANDKING2",0x3AF8C345,"SANDKIN2","Off-Road","Sandking SWB","Vapid")
VehiclesAddToTable("SAVAGE",0xFB133A17,"SAVAGE","Helicopters","Savage","")
VehiclesAddToTable("SCHAFTER2",0xB52B5113,"SCHAFTER","SUVs","Schafter","Benefactor")
VehiclesAddToTable("SCHAFTER3",0xA774B5A6,"SCHAFTER3","Sports","Schafter V12","Benefactor")
VehiclesAddToTable("SCHAFTER4",0x58CF185C,"SCHAFTER4","Sports","Schafter LWB","Benefactor")
VehiclesAddToTable("SCHAFTER5",0xCB0E7CD9,"SCHAFTER5","SUVs","Schafter V12 (Armored)","Benefactor")
VehiclesAddToTable("SCHAFTER6",0x72934BE4,"SCHAFTER6","SUVs","Schafter LWB (Armored)","Benefactor")
VehiclesAddToTable("SCHWARZER",0xD37B7976,"SCHWARZE","Sports","Schwartzer","Benefactor")
VehiclesAddToTable("SCORCHER",0xF4E1AA15,"SCORCHER","Bicycles","Scorcher","")
VehiclesAddToTable("SCRAP",0x9A9FD3DF,"SCRAP","Utility","Scrap Truck","")
VehiclesAddToTable("SEASHARK",0xC2974024,"SEASHARK","Boats","Seashark","Speedophile")
VehiclesAddToTable("SEASHARK2",0xDB4388E4,"SEASHARK","Boats","Seashark","Speedophile")
VehiclesAddToTable("SEASHARK3",0xED762D49,"SEASHARK","Boats","Seashark","Speedophile")
VehiclesAddToTable("SEMINOLE",0x48CECED3,"SEMINOLE","Sedans","Seminole","Canis")
VehiclesAddToTable("SENTINEL",0x50732C82,"SENTINEL","Coupes","Sentinel XS","Ubermacht")
VehiclesAddToTable("SENTINEL2",0x3412AE2D,"SENTINEL2","Coupes","Sentinel","Ubermacht")
VehiclesAddToTable("SERRANO",0x4FB1A214,"SERRANO","Sedans","Serrano","Benefactor")
VehiclesAddToTable("SHAMAL",0xB79C1BF5,"SHAMAL","Airplanes","Shamal","Buckingham")
VehiclesAddToTable("SHERIFF",0x9BAA707C,"SHERIFF","Emergency","Sheriff Cruiser","")
VehiclesAddToTable("SHERIFF2",0x72935408,"SHERIFF2","Emergency","Sheriff SUV","")
VehiclesAddToTable("SKYLIFT",0x3E48BF23,"SKYLIFT","Helicopters","Skylift","")
VehiclesAddToTable("SLAMVAN",0x2B7F9DE3,"SLAMVAN","Muscle","Slamvan","Vapid")
VehiclesAddToTable("SLAMVAN2",0x31ADBBFC,"SLAMVAN2","Muscle","Lost Slamvan","Vapid")
VehiclesAddToTable("SOVEREIGN",0x2C509634,"SOVEREIGN","Motorcycles","Sovereign","Western")
VehiclesAddToTable("SPEEDER",0xDC60D2B,"SPEEDER","Boats","Speeder","Pegassi")
VehiclesAddToTable("SPEEDER2",0x1A144F2A,"SPEEDER","Boats","Speeder","Pegassi")
VehiclesAddToTable("SPEEDO",0xCFB3870C,"SPEEDO","Vans/Pickups","Speedo","Vapid")
VehiclesAddToTable("SPEEDO2",0x2B6DC64A,"SPEEDO2","Vans/Pickups","Clown Van","Vapid")
VehiclesAddToTable("SQUALO",0x17DF5EC2,"SQUALO","Boats","Squalo","Shitzu")
VehiclesAddToTable("STALION",0x72A4C31E,"STALION","Muscle","Stallion","Declasse")
VehiclesAddToTable("STALION2",0xE80F67EE,"STALION2","Muscle","Burger Shot Stallion","Declasse")
VehiclesAddToTable("STANIER",0xA7EDE74D,"STANIER","SUVs","Stanier","Vapid")
VehiclesAddToTable("STINGER",0x5C23AF9B,"STINGER","Sports Classics","Stinger","Grotti")
VehiclesAddToTable("STINGERGT",0x82E499FA,"STINGERG","Sports Classics","Stinger GT","Grotti")
VehiclesAddToTable("STOCKADE",0x6827CF72,"STOCKADE","Commercial","Stockade","Brute")
VehiclesAddToTable("STOCKADE3",0xF337AB36,"STOCKADE","Commercial","Stockade","Brute")
VehiclesAddToTable("STRATUM",0x66B4FC45,"STRATUM","SUVs","Stratum","Zirconium")
VehiclesAddToTable("STRETCH",0x8B13F083,"STRETCH","SUVs","Stretch","Dundreary")
VehiclesAddToTable("STUNT",0x81794C70,"STUNT","Airplanes","Mallard","")
VehiclesAddToTable("SUBMERSIBLE",0x2DFF622F,"SUBMERS","Boats","Submersible","")
VehiclesAddToTable("SUBMERSIBLE2",0xC07107EE,"SUBMERS2","Boats","Kraken","")
VehiclesAddToTable("SULTAN",0x39DA2754,"SULTAN","Sports","Sultan","Karin")
VehiclesAddToTable("SUNTRAP",0xEF2295C9,"SUNTRAP","Boats","Suntrap","Shitzu")
VehiclesAddToTable("SUPERD",0x42F2ED16,"SUPERD","SUVs","Super Diamond","Enus")
VehiclesAddToTable("SUPERVOLITO",0x2A54C47D,"SVOLITO","Helicopters","SuperVolito","Buckingham")
VehiclesAddToTable("SUPERVOLITO2",0x9C5E5644,"SVOLITO2","Helicopters","SuperVolito Carbon","Buckingham")
VehiclesAddToTable("SURANO",0x16E478C1,"SURANO","Sports","Surano","Benefactor")
VehiclesAddToTable("SURFER",0x29B0DA97,"SURFER","Vans/Pickups","Surfer","BF")
VehiclesAddToTable("SURFER2",0xB1D80E06,"SURFER2","Vans/Pickups","Surfer","BF")
VehiclesAddToTable("SURGE",0x8F0E3594,"SURGE","SUVs","Surge","Cheval")
VehiclesAddToTable("SWIFT",0xEBC24DF2,"SWIFT","Helicopters","Swift","Buckingham")
VehiclesAddToTable("SWIFT2",0x4019CB4C,"SWIFT2","Helicopters","Swift Deluxe","Buckingham")
VehiclesAddToTable("T20",0x6322B39A,"T20","Super","T20","Progen")
VehiclesAddToTable("TACO",0x744CA80D,"TACO","Vans/Pickups","Taco Van","")
VehiclesAddToTable("TAILGATER",0xC3DDFDCE,"TAILGATE","SUVs","Tailgater","Obey")
VehiclesAddToTable("TAMPA",0x39F9C898,"TAMPA","Muscle","Tampa","Declasse")
VehiclesAddToTable("TANKER",0xD46F4737,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TANKER2",0x74998082,"TANKER","Utility","NULL","")
VehiclesAddToTable("TANKERCAR",0x22EDDC30,"FREIGHT","Trains","Freight Train","")
VehiclesAddToTable("TAXI",0xC703DB5F,"TAXI","Service","Taxi","")
VehiclesAddToTable("TECHNICAL",0x83051506,"TECHNICAL","Off-Road","Technical","Karin")
VehiclesAddToTable("THRUST",0x6D6F8F43,"THRUST","Motorcycles","Thrust","Dinka")
VehiclesAddToTable("TIPTRUCK",0x2E19879,"TIPTRUCK","Industrial","Tipper","Brute")
VehiclesAddToTable("TIPTRUCK2",0xC7824E5E,"TIPTRUCK2","Industrial","Tipper","")
VehiclesAddToTable("TITAN",0x761E2AD3,"TITAN","Airplanes","Titan","")
VehiclesAddToTable("TORNADO",0x1BB290BC,"TORNADO","Sports Classics","Tornado","Declasse")
VehiclesAddToTable("TORNADO2",0x5B42A5C4,"TORNADO2","Sports Classics","Tornado","Declasse")
VehiclesAddToTable("TORNADO3",0x690A4153,"TORNADO3","Sports Classics","Tornado","Declasse")
VehiclesAddToTable("TORNADO4",0x86CF7CDD,"TORNADO","Sports Classics","Tornado","Declasse")
VehiclesAddToTable("TORO",0x3FD5AA2F,"TORO","Boats","Toro","Lampadati")
VehiclesAddToTable("TORO2",0x362CAC6D,"TORO","Boats","Toro","Lampadati")
VehiclesAddToTable("TOURBUS",0x73B1C3CB,"TOURBUS","Service","Tourbus","")
VehiclesAddToTable("TOWTRUCK",0xB12314E0,"TOWTRUCK","Utility","Towtruck","")
VehiclesAddToTable("TOWTRUCK2",0xE5A2D6C6,"TOWTRUCK","Utility","Towtruck","")
VehiclesAddToTable("TR2",0x7BE032C6,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TR3",0x6A59902D,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TR4",0x7CAB34D0,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TRACTOR",0x61D6BA8C,"TRACTOR","Utility","Tractor","")
VehiclesAddToTable("TRACTOR2",0x843B73DE,"TRACTOR2","Utility","Fieldmaster","Stanley")
VehiclesAddToTable("TRACTOR3",0x562A97BD,"TRACTOR2","Utility","Fieldmaster","Stanley")
VehiclesAddToTable("TRAILERLOGS",0x782A236D,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TRAILERS",0xCBB2BE0E,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TRAILERS2",0xA1DA3C91,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TRAILERS3",0x8548036D,"TRAILERS3","Utility","Trailer","")
VehiclesAddToTable("TRAILERSMALL",0x2A72BEAB,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TRASH",0x72435A19,"TRASH","Service","Trashmaster","")
VehiclesAddToTable("TRASH2",0xB527915C,"TRASH","Service","Trashmaster","")
VehiclesAddToTable("TRFLAT",0xAF62F6B2,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("TRIBIKE",0x4339CD69,"TRIBIKE","Bicycles","Whippet Race Bike","")
VehiclesAddToTable("TRIBIKE2",0xB67597EC,"TRIBIKE2","Bicycles","Endurex Race Bike","")
VehiclesAddToTable("TRIBIKE3",0xE823FB48,"TRIBIKE3","Bicycles","Tri-Cycles Race Bike","")
VehiclesAddToTable("TROPIC",0x1149422F,"TROPIC","Boats","Tropic","Shitzu")
VehiclesAddToTable("TROPIC2",0x56590FE9,"TROPIC","Boats","Tropic","Shitzu")
VehiclesAddToTable("TURISMOR",0x185484E1,"TURISMOR","Super","Turismo R","Grotti")
VehiclesAddToTable("TVTRAILER",0x967620BE,"TRAILER","Utility","Trailer","")
VehiclesAddToTable("UTILLITRUCK",0x1ED0A534,"UTILTRUC","Utility","Utility Truck","")
VehiclesAddToTable("UTILLITRUCK2",0x34E6BF6B,"UTILTRUC","Utility","Utility Truck","")
VehiclesAddToTable("UTILLITRUCK3",0x7F2153DF,"UTILTRUC","Utility","Utility Truck","")
VehiclesAddToTable("VACCA",0x142E0DC3,"VACCA","Super","Vacca","Pegassi")
VehiclesAddToTable("VADER",0xF79A00F7,"VADER","Motorcycles","Vader","Shitzu")
VehiclesAddToTable("VALKYRIE",0xA09E15FD,"VALKYRIE","Helicopters","Valkyrie","")
VehiclesAddToTable("VALKYRIE2",0x5BFA5C4B,"VALKYRI2","Helicopters","Valkyrie MOD.0","")
VehiclesAddToTable("VELUM",0x9C429B6A,"VELUM","Airplanes","Velum","")
VehiclesAddToTable("VELUM2",0x403820E8,"VELUM2","Airplanes","Velum 5-Seater","")
VehiclesAddToTable("VERLIERER2",0x41B77FA4,"VERLIER","Sports","Verlierer","Bravado")
VehiclesAddToTable("VESTRA",0x4FF77E37,"VESTRA","Airplanes","Vestra","Buckingham")
VehiclesAddToTable("VIGERO",0xCEC6B9B7,"VIGERO","Muscle","Vigero","Declasse")
VehiclesAddToTable("VINDICATOR",0xAF599F01,"VINDICATOR","Motorcycles","Vindicator","Dinka")
VehiclesAddToTable("VIRGO",0xE2504942,"VIRGO","Muscle","Virgo","Albany")
VehiclesAddToTable("VOLTIC",0x9F4B77BE,"VOLTIC","Super","Voltic","Coil")
VehiclesAddToTable("VOODOO",0x779B4F2D,"VOODOO2","Muscle","Voodoo Custom","Declasse")
VehiclesAddToTable("VOODOO2",0x1F3766E3,"VOODOO","Muscle","Voodoo","Declasse")
VehiclesAddToTable("WARRENER",0x51D83328,"WARRENER","SUVs","Warrener","Vulcar")
VehiclesAddToTable("WASHINGTON",0x69F06B57,"WASHINGT","SUVs","Washington","Albany")
VehiclesAddToTable("WINDSOR",0x5E4327C8,"WINDSOR","Coupes","Windsor","Enus")
VehiclesAddToTable("YOUGA",0x3E5F6B8,"YOUGA","Vans/Pickups","Youga","Bravado")
VehiclesAddToTable("ZENTORNO",0xAC5DF515,"ZENTORNO","Super","Zentorno","Pegassi")
VehiclesAddToTable("ZION",0xBD1B39C3,"ZION","Coupes","Zion","Ubermacht")
VehiclesAddToTable("ZION2",0xB8E2AE18,"ZION2","Coupes","Zion Cabrio","Ubermacht")
VehiclesAddToTable("ZTYPE",0x2D3BD401,"ZTYPE","Sports Classics","Z-Type","Truffade")

VEHICLE_CARGOBOB = 0xFCFCB68B
VEHICLE_POLICE = 0x79FBB0C5
VEHICLE_RANCHERXL2 = 0x7341576B
VEHICLE_ALPHA = 0x2DB8D1AA
VEHICLE_SCORCHER = 0xF4E1AA15
VEHICLE_NEMESIS = 0xDA288376
VEHICLE_POLICE4 = 0x8A63C7B9
VEHICLE_DOMINATOR = 0x4CE68AC
VEHICLE_BLAZER3 = 0xB44F0582
VEHICLE_CHINO2 = 0xAED64A63
VEHICLE_BARRACKS2 = 0x4008EABB
VEHICLE_BODHI2 = 0xAA699BB6
VEHICLE_MARQUIS = 0xC1CE1183
VEHICLE_ELEGY2 = 0xDE3D9D22
VEHICLE_SCHAFTER2 = 0xB52B5113
VEHICLE_FORKLIFT = 0x58E49664
VEHICLE_DUSTER = 0x39D6779E
VEHICLE_TECHNICAL = 0x83051506
VEHICLE_INSURGENT2 = 0x7B7E56F0
VEHICLE_EMPEROR2 = 0x8FC3AADC
VEHICLE_SULTAN = 0x39DA2754
VEHICLE_BOBCATXL = 0x3FC5D440
VEHICLE_VOODOO = 0x779B4F2D
VEHICLE_JESTER = 0xB2A716A3
VEHICLE_BALLER6 = 0x27B4E6B0
VEHICLE_BUZZARD2 = 0x2C75F0DD
VEHICLE_METROTRAIN = 0x33C9E158
VEHICLE_SKYLIFT = 0x3E48BF23
VEHICLE_FIXTER = 0xCE23D3BF
VEHICLE_HAKUCHOU = 0x4B6C568A
VEHICLE_FIRETRUK = 0x73920F8E
VEHICLE_PREMIER = 0x8FB66F9B
VEHICLE_BIFTA = 0xEB298297
VEHICLE_BTYPE2 = 0xCE6B35A4
VEHICLE_STINGERGT = 0x82E499FA
VEHICLE_PEYOTE = 0x6D19CCBC
VEHICLE_TRFLAT = 0xAF62F6B2
VEHICLE_DUBSTA3 = 0xB6410173
VEHICLE_SENTINEL2 = 0x3412AE2D
VEHICLE_BUFFALO = 0xEDD516C6
VEHICLE_SCHAFTER4 = 0x58CF185C
VEHICLE_ASEA = 0x94204D89
VEHICLE_BUFFALO3 = 0xE2C013E
VEHICLE_RHAPSODY = 0x322CF98F
VEHICLE_ROCOTO = 0x7F5C91F1
VEHICLE_TRASH = 0x72435A19
VEHICLE_FUSILADE = 0x1DC0BA53
VEHICLE_FELTZER2 = 0x8911B9F5
VEHICLE_AMBULANCE = 0x45D56ADA
VEHICLE_SLAMVAN = 0x2B7F9DE3
VEHICLE_BLADE = 0xB820ED5E
VEHICLE_SHERIFF = 0x9BAA707C
VEHICLE_BFINJECTION = 0x432AA566
VEHICLE_FROGGER2 = 0x742E9AC0
VEHICLE_LAZER = 0xB39B0AE6
VEHICLE_FACTION2 = 0x95466BDB
VEHICLE_JB700 = 0x3EAB5555
VEHICLE_ARMYTRAILER2 = 0x9E6B14D6
VEHICLE_FUGITIVE = 0x71CB2FFB
VEHICLE_CASCO = 0x3822BDFE
VEHICLE_DINGHY2 = 0x107F392C
VEHICLE_BESRA = 0x6CBD1D6D
VEHICLE_HOTKNIFE = 0x239E390
VEHICLE_BALLER4 = 0x25CBE2E2
VEHICLE_RAKETRAILER = 0x174CB172
VEHICLE_AIRTUG = 0x5D0AAC8F
VEHICLE_MOWER = 0x6A4BD8F6
VEHICLE_GAUNTLET2 = 0x14D22159
VEHICLE_BURRITO = 0xAFBB2CA4
VEHICLE_TORO = 0x3FD5AA2F
VEHICLE_ANNIHILATOR = 0x31F0B376
VEHICLE_BUZZARD = 0x2F03547B
VEHICLE_DINGHY3 = 0x1E5E54EA
VEHICLE_MASSACRO = 0xF77ADE32
VEHICLE_CARGOBOB4 = 0x78BC1A3C
VEHICLE_BISON = 0xFEFD644F
VEHICLE_EXEMPLAR = 0xFFB15B5E
VEHICLE_DUBSTA = 0x462FE277
VEHICLE_TRACTOR2 = 0x843B73DE
VEHICLE_ENDURO = 0x6882FA73
VEHICLE_VESTRA = 0x4FF77E37
VEHICLE_BISON3 = 0x67B3F020
VEHICLE_CARGOPLANE = 0x15F27762
VEHICLE_FAGGIO2 = 0x350D1AB
VEHICLE_CUBAN800 = 0xD9927FE3
VEHICLE_LUXOR = 0x250B0C5E
VEHICLE_BJXL = 0x32B29A4B
VEHICLE_COG552 = 0x29FCD3E4
VEHICLE_SUPERVOLITO2 = 0x9C5E5644
VEHICLE_STRETCH = 0x8B13F083
VEHICLE_INFERNUS = 0x18F25AC7
VEHICLE_CARBONIZZARE = 0x7B8AB45F
VEHICLE_LUXOR2 = 0xB79F589E
VEHICLE_DLOADER = 0x698521E3
VEHICLE_GLENDALE = 0x47A6BC1
VEHICLE_COGNOSCENTI2 = 0xDBF2D57A
VEHICLE_POUNDER = 0x7DE35E7D
VEHICLE_RADI = 0x9D96B45B
VEHICLE_BATI = 0xF9300CC5
VEHICLE_FBI2 = 0x9DC66994
VEHICLE_ZION2 = 0xB8E2AE18
VEHICLE_MONROE = 0xE62B361B
VEHICLE_SLAMVAN2 = 0x31ADBBFC
VEHICLE_ASTEROPE = 0x8E9254FB
VEHICLE_MANANA = 0x81634188
VEHICLE_DUBSTA2 = 0xE882E5F6
VEHICLE_BAGGER = 0x806B9CC3
VEHICLE_COGNOSCENTI = 0x86FE0B60
VEHICLE_CAVALCADE2 = 0xD0EB2BE5
VEHICLE_ZION = 0xBD1B39C3
VEHICLE_MESA2 = 0xD36A4B44
VEHICLE_TORO2 = 0x362CAC6D
VEHICLE_ORACLE2 = 0xE18195B2
VEHICLE_INSURGENT = 0x9114EADA
VEHICLE_SURANO = 0x16E478C1
VEHICLE_KALAHARI = 0x5852838
VEHICLE_PATRIOT = 0xCFCFEB3B
VEHICLE_COQUETTE2 = 0x3C4E2113
VEHICLE_POLICE2 = 0x9F05F101
VEHICLE_COQUETTE = 0x67BC037
VEHICLE_BALETRAILER = 0xE82AE656
VEHICLE_SEASHARK3 = 0xED762D49
VEHICLE_TRASH2 = 0xB527915C
VEHICLE_DOCKTUG = 0xCB44B1CA
VEHICLE_HANDLER = 0x1A7FCEFA
VEHICLE_STALION2 = 0xE80F67EE
VEHICLE_VOODOO2 = 0x1F3766E3
VEHICLE_GBURRITO = 0x97FA4F36
VEHICLE_INGOT = 0xB3206692
VEHICLE_YOUGA = 0x3E5F6B8
VEHICLE_DINGHY4 = 0x33B47F96
VEHICLE_REBEL2 = 0x8612B64B
VEHICLE_MOONBEAM2 = 0x710A2B9B
VEHICLE_ZTYPE = 0x2D3BD401
VEHICLE_DILETTANTE = 0xBC993509
VEHICLE_BUFFALO2 = 0x2BEC3CBE
VEHICLE_ZENTORNO = 0xAC5DF515
VEHICLE_FREIGHTCONT2 = 0xE512E79
VEHICLE_FACTION = 0x81A9CDDF
VEHICLE_DODO = 0xCA495705
VEHICLE_SHAMAL = 0xB79C1BF5
VEHICLE_TOWTRUCK = 0xB12314E0
VEHICLE_VALKYRIE2 = 0x5BFA5C4B
VEHICLE_SCRAP = 0x9A9FD3DF
VEHICLE_FELON2 = 0xFAAD85EE
VEHICLE_STANIER = 0xA7EDE74D
VEHICLE_BURRITO4 = 0x353B561D
VEHICLE_VIRGO = 0xE2504942
VEHICLE_CABLECAR = 0xC6C3242D
VEHICLE_SERRANO = 0x4FB1A214
VEHICLE_PBUS = 0x885F3671
VEHICLE_POLICEB = 0xFDEFAEC3
VEHICLE_COQUETTE3 = 0x2EC385FE
VEHICLE_VINDICATOR = 0xAF599F01
VEHICLE_VIGERO = 0xCEC6B9B7
VEHICLE_VERLIERER2 = 0x41B77FA4
VEHICLE_RUBBLE = 0x9A5B1DCC
VEHICLE_VELUM2 = 0x403820E8
VEHICLE_VELUM = 0x9C429B6A
VEHICLE_WARRENER = 0x51D83328
VEHICLE_AIRBUS = 0x4C80EB0E
VEHICLE_HAULER = 0x5A82F9AE
VEHICLE_VALKYRIE = 0xA09E15FD
VEHICLE_JET = 0x3F119114
VEHICLE_BOXVILLE2 = 0xF21B33BE
VEHICLE_TRAILERSMALL = 0x2A72BEAB
VEHICLE_TRIBIKE = 0x4339CD69
VEHICLE_UTILLITRUCK3 = 0x7F2153DF
VEHICLE_UTILLITRUCK2 = 0x34E6BF6B
VEHICLE_UTILLITRUCK = 0x1ED0A534
VEHICLE_TVTRAILER = 0x967620BE
VEHICLE_MIXER = 0xD138A6BB
VEHICLE_TURISMOR = 0x185484E1
VEHICLE_TROPIC2 = 0x56590FE9
VEHICLE_DUNE2 = 0x1FD824AF
VEHICLE_TROPIC = 0x1149422F
VEHICLE_TRIBIKE3 = 0xE823FB48
VEHICLE_TRIBIKE2 = 0xB67597EC
VEHICLE_SCHAFTER5 = 0xCB0E7CD9
VEHICLE_FREIGHTGRAIN = 0x264D9262
VEHICLE_VACCA = 0x142E0DC3
VEHICLE_VADER = 0xF79A00F7
VEHICLE_BLISTA = 0xEB70965F
VEHICLE_MOONBEAM = 0x1F52A43F
VEHICLE_BIFF = 0x32B91AE8
VEHICLE_GRAINTRAILER = 0x3CC7F596
VEHICLE_BALLER2 = 0x8852855
VEHICLE_DUKES2 = 0xEC8F7094
VEHICLE_TRAILERS3 = 0x8548036D
VEHICLE_TRAILERS2 = 0xA1DA3C91
VEHICLE_REBEL = 0xB802DD46
VEHICLE_TRAILERS = 0xCBB2BE0E
VEHICLE_BALLER3 = 0x6FF0F727
VEHICLE_SANCHEZ = 0x2EF89E46
VEHICLE_SUPERD = 0x42F2ED16
VEHICLE_TRACTOR3 = 0x562A97BD
VEHICLE_SPEEDER2 = 0x1A144F2A
VEHICLE_TRACTOR = 0x61D6BA8C
VEHICLE_EMPEROR3 = 0xB5FCF74E
VEHICLE_TR4 = 0x7CAB34D0
VEHICLE_TR3 = 0x6A59902D
VEHICLE_NIGHTSHADE = 0x8C2BD0DC
VEHICLE_TOWTRUCK2 = 0xE5A2D6C6
VEHICLE_DUNE = 0x9CF21E0F
VEHICLE_WASHINGTON = 0x69F06B57
VEHICLE_TOURBUS = 0x73B1C3CB
VEHICLE_TORNADO4 = 0x86CF7CDD
VEHICLE_BUCCANEER = 0xD756460C
VEHICLE_TORNADO3 = 0x690A4153
VEHICLE_STRATUM = 0x66B4FC45
VEHICLE_FLATBED = 0x50B0215A
VEHICLE_MULE2 = 0xC1632BEB
VEHICLE_TORNADO = 0x1BB290BC
VEHICLE_PACKER = 0x21EEE87D
VEHICLE_TITAN = 0x761E2AD3
VEHICLE_TIPTRUCK2 = 0xC7824E5E
VEHICLE_TIPTRUCK = 0x2E19879
VEHICLE_THRUST = 0x6D6F8F43
VEHICLE_PCJ = 0xC9CEAF06
VEHICLE_BALLER5 = 0x1C09CF5E
VEHICLE_TAXI = 0xC703DB5F
VEHICLE_SUBMERSIBLE = 0x2DFF622F
VEHICLE_FBI = 0x432EA949
VEHICLE_TANKERCAR = 0x22EDDC30
VEHICLE_FQ2 = 0xBC32A33B
VEHICLE_KHAMELION = 0x206D1B68
VEHICLE_BISON2 = 0x7B8297C5
VEHICLE_SURGE = 0x8F0E3594
VEHICLE_TAMPA = 0x39F9C898
VEHICLE_CARGOBOB3 = 0x53174EEF
VEHICLE_TAILGATER = 0xC3DDFDCE
VEHICLE_TACO = 0x744CA80D
VEHICLE_SCHWARZER = 0xD37B7976
VEHICLE_SWIFT2 = 0x4019CB4C
VEHICLE_SWIFT = 0xEBC24DF2
VEHICLE_BLISTA3 = 0xDCBC1C3B
VEHICLE_TANKER = 0xD46F4737
VEHICLE_SURFER2 = 0xB1D80E06
VEHICLE_POLICE3 = 0x71FA16EA
VEHICLE_FELTZER3 = 0xA29D6D10
VEHICLE_SURFER = 0x29B0DA97
VEHICLE_WINDSOR = 0x5E4327C8
VEHICLE_MULE = 0x35ED670B
VEHICLE_NINEF = 0x3D8FA25C
VEHICLE_SUNTRAP = 0xEF2295C9
VEHICLE_T20 = 0x6322B39A
VEHICLE_STUNT = 0x81794C70
VEHICLE_BLIMP2 = 0xDB6B4924
VEHICLE_TORNADO2 = 0x5B42A5C4
VEHICLE_HABANERO = 0x34B7390F
VEHICLE_STOCKADE3 = 0xF337AB36
VEHICLE_STOCKADE = 0x6827CF72
VEHICLE_GRANGER = 0x9628879C
VEHICLE_KURUMA2 = 0x187D938D
VEHICLE_EMPEROR = 0xD7278283
VEHICLE_ISSI2 = 0xB9CB3B69
VEHICLE_PONY2 = 0x38408341
VEHICLE_FELON = 0xE8A8BDA8
VEHICLE_SQUALO = 0x17DF5EC2
VEHICLE_PICADOR = 0x59E0FBF3
VEHICLE_FREIGHTCAR = 0xAFD22A6
VEHICLE_INNOVATION = 0xF683EACA
VEHICLE_BURRITO2 = 0xC9E8FF76
VEHICLE_FROGGER = 0x2C634FBD
VEHICLE_RUINER = 0xF26CEFF9
VEHICLE_SPEEDER = 0xDC60D2B
VEHICLE_SOVEREIGN = 0x2C509634
VEHICLE_MASSACRO2 = 0xDA5819A3
VEHICLE_SUPERVOLITO = 0x2A54C47D
VEHICLE_SENTINEL = 0x50732C82
VEHICLE_CADDY2 = 0xDFF0594C
VEHICLE_PARADISE = 0x58B3979C
VEHICLE_SEMINOLE = 0x48CECED3
VEHICLE_SABREGT = 0x9B909C94
VEHICLE_STALION = 0x72A4C31E
VEHICLE_KURUMA = 0xAE2BFE94
VEHICLE_VOLTIC = 0x9F4B77BE
VEHICLE_INTRUDER = 0x34DD8AA1
VEHICLE_SUBMERSIBLE2 = 0xC07107EE
VEHICLE_BMX = 0x43779C54
VEHICLE_FREIGHT = 0x3D6AAA9B
VEHICLE_COACH = 0x84718D34
VEHICLE_ENTITYXF = 0xB2FE5CF9
VEHICLE_BOATTRAILER = 0x1F3D44B5
VEHICLE_SCHAFTER6 = 0x72934BE4
VEHICLE_SCHAFTER3 = 0xA774B5A6
VEHICLE_SAVAGE = 0xFB133A17
VEHICLE_SANDKING2 = 0x3AF8C345
VEHICLE_FUTO = 0x7836CE2F
VEHICLE_HEXER = 0x11F76C14
VEHICLE_JACKAL = 0xDAC67112
VEHICLE_SADLER2 = 0x2BC345D1
VEHICLE_MAMMATUS = 0x97E55D11
VEHICLE_DUKES = 0x2B26F456
VEHICLE_RAPIDGT = 0x8CB29A14
VEHICLE_CHINO = 0x14D69010
VEHICLE_TRAILERLOGS = 0x782A236D
VEHICLE_CADDY = 0x44623884
VEHICLE_PRIMO = 0xBB6B404F
VEHICLE_SADLER = 0xDC434E51
VEHICLE_CRUISER = 0x1ABA13B5
VEHICLE_DUMP = 0x810369E2
VEHICLE_DOMINATOR2 = 0xC96B73D9
VEHICLE_HYDRA = 0x39D6E83F
VEHICLE_BENSON = 0x7A61B330
VEHICLE_BOXVILLE3 = 0x7405E08
VEHICLE_POLMAV = 0x1517D4D9
VEHICLE_REGINA = 0xFF22D208
VEHICLE_PENUMBRA = 0xE9805550
VEHICLE_ROMERO = 0x2560B2FC
VEHICLE_STINGER = 0x5C23AF9B
VEHICLE_RIOT = 0xB822A1AA
VEHICLE_RHINO = 0x2EA68690
VEHICLE_BALLER = 0xCFCA3668
VEHICLE_NINEF2 = 0xA8E38B01
VEHICLE_PIGALLE = 0x404B6381
VEHICLE_RENTALBUS = 0xBE819C63
VEHICLE_COGCABRIO = 0x13B57D8A
VEHICLE_RUFFIAN = 0xCABD11E8
VEHICLE_RUMPO = 0x4543B74D
VEHICLE_CARGOBOB2 = 0x60A7EA10
VEHICLE_DAEMON = 0x77934CEE
VEHICLE_MESA = 0x36848602
VEHICLE_LECTRO = 0x26321E67
VEHICLE_HUNTLEY = 0x1D06D681
VEHICLE_SANCHEZ2 = 0xA960B13E
VEHICLE_RANCHERXL = 0x6210CBB0
VEHICLE_PROPTRAILER = 0x153E1B0A
VEHICLE_GUARDIAN = 0x825A9F4C
VEHICLE_PRIMO2 = 0x86618EDA
VEHICLE_CUTTER = 0xC3FBA120
VEHICLE_ARMYTRAILER = 0xA7FF33F5
VEHICLE_PREDATOR = 0xE2E7D4AB
VEHICLE_PRANGER = 0x2C33B46E
VEHICLE_MULE3 = 0x85A5B471
VEHICLE_TR2 = 0x7BE032C6
VEHICLE_PONY = 0xF8DE29A8
VEHICLE_ORACLE = 0x506434F6
VEHICLE_JETMAX = 0x33581161
VEHICLE_POLICET = 0x1B38E955
VEHICLE_POLICEOLD2 = 0x95F4C618
VEHICLE_DOUBLE = 0x9C669788
VEHICLE_ARMYTANKER = 0xB8081009
VEHICLE_AKUMA = 0x63ABADE7
VEHICLE_POLICEOLD1 = 0xA46462F7
VEHICLE_DILETTANTE2 = 0x64430650
VEHICLE_BULLET = 0x9AE6DDA1
VEHICLE_MONSTER = 0xCD93A7DB
VEHICLE_BOXVILLE4 = 0x1A79847A
VEHICLE_SPEEDO2 = 0x2B6DC64A
VEHICLE_BLIMP = 0xF7004C86
VEHICLE_DINGHY = 0x3D961290
VEHICLE_BARRACKS3 = 0x2592B5CF
VEHICLE_PHOENIX = 0x831A21D5
VEHICLE_OSIRIS = 0x767164D6
VEHICLE_PHANTOM = 0x809AA4CB
VEHICLE_MINIVAN = 0xED7EADA4
VEHICLE_JOURNEY = 0xF8D48E7A
VEHICLE_BRAWLER = 0xA7CE1BC5
VEHICLE_ASEA2 = 0x9441D8D5
VEHICLE_JESTER2 = 0xBE0E6126
VEHICLE_PANTO = 0xE644E480
VEHICLE_CAMPER = 0x6FD95F68
VEHICLE_LIMO2 = 0xF92AEC4D
VEHICLE_CAVALCADE = 0x779F23AA
VEHICLE_COMET2 = 0xC1AE4D16
VEHICLE_BANSHEE = 0xC1E908D2
VEHICLE_SPEEDO = 0xCFB3870C
VEHICLE_BTYPE = 0x6FF6914
VEHICLE_BURRITO5 = 0x437CF2A0
VEHICLE_MAVERICK = 0x9D0450CA
VEHICLE_PRAIRIE = 0xA988D3A2
VEHICLE_COG55 = 0x360A438E
VEHICLE_BULLDOZER = 0x7074F39D
VEHICLE_BATI2 = 0xCADD5D2D
VEHICLE_SANDKING = 0xB9210FD0
VEHICLE_BARRACKS = 0xCEEA3F4B
VEHICLE_GBURRITO2 = 0x11AA0E14
VEHICLE_MIXER2 = 0x1C534995
VEHICLE_MILJET = 0x9D80F93
VEHICLE_BUS = 0xD577C962
VEHICLE_MESA3 = 0x84F42E51
VEHICLE_BLAZER = 0x8125BCF9
VEHICLE_BUCCANEER2 = 0xC397F748
VEHICLE_RATLOADER = 0xD83C13CE
VEHICLE_SHERIFF2 = 0x72935408
VEHICLE_RAPIDGT2 = 0x679450AF
VEHICLE_ADDER = 0xB779A091
VEHICLE_BLISTA2 = 0x3DEE5EDA
VEHICLE_MARSHALL = 0x49863E9C
VEHICLE_CRUSADER = 0x132D5A1A
VEHICLE_MAMBA = 0x9CFFFC56
VEHICLE_RUMPO2 = 0x961AFEF7
VEHICLE_SEASHARK2 = 0xDB4388E4
VEHICLE_FREIGHTTRAILER = 0xD1ABB666
VEHICLE_CHEETAH = 0xB1D95DA0
VEHICLE_LGUARD = 0x1BF8D381
VEHICLE_LANDSTALKER = 0x4BA4E8DC
VEHICLE_LURCHER = 0x7B47A6A7
VEHICLE_RIPLEY = 0xCD935EF9
VEHICLE_CARBONRS = 0xABB0C0
VEHICLE_BURRITO3 = 0x98171BD3
VEHICLE_SEASHARK = 0xC2974024
VEHICLE_TANKER2 = 0x74998082
VEHICLE_DOCKTRAILER = 0x806EFBEE
VEHICLE_GRESLEY = 0xA3FC0F4D
VEHICLE_BLAZER2 = 0xFD231729
VEHICLE_RATLOADER2 = 0xDCE1D9F7
VEHICLE_GAUNTLET = 0x94B395C5
VEHICLE_FUROREGT = 0xBF1691E0
VEHICLE_FREIGHTCONT1 = 0x36DCFF98
VEHICLE_F620 = 0xDCBCBE48
VEHICLE_BOXVILLE = 0x898ECCEA

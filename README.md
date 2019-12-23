
<img align="left" width="170" height="40" src="https://github.com/plasmadlt/NFT-and-NTT-Protocol/img/plasmadltlogo.png"> </br>

***
# NFT and NTT Protocol
***

## Сontent:
* [Introduction](#introduction)
* [Protocol Applicability](#protocol-applicability)
  * [Games](#games)
  * [Collectibles](#collectibles)
  * [Licensing](#licensing)
* [Contracts Actions](#contracts-actions)
* [Contracts Structures](#contracts-structures)
   * [Assets options](#assets-options)
   * [Offers options](#offers-options)
   * [Authors options](#authors-options)
   * [Lending](#Lending)
   * [NTT asset options](#ntt-asset-options)
* [Example: Sol interface NFT assets](#examples-sol-interface-nft-assets)
  * [Setup](#setup)
    * [Build Contract](#build-contract)
    * [Deploy Contract](#delpoy-contract)
* [Example: Sol interface NTT assets](#examples-sol-interface-ntt-assets)

---------------------------

# Introduction

A protocol  for digital assets on PlasmaDLT blockchains: Non-Fungible Tokens (NFT) and Non-Transferable Tokens (NTT).
The use of NFT and NTT tokens simplifies the creation and makes ownership safe for unique characters and game items where the player can own, sell and exchange assets between other players and services. Within the blockchain, this allows you to instantly show that each side has the means at hand, while at the same time ensuring that the transfer of property rights belongs to this unique token with which the seller shares visibility on the blockchain. In-game resources - such as tokens or gold - are interchangeable, but some rare high-level items, perhaps the legendary sword or vehicle, may not be interchangeable.

Protocol Features:

* Adding (url, img, webgl, mp3, video, hide)
* Change of author
* Change of ownership
* Lending (transfer to temporary possession)

Useful links:
* Wallet: https://plasmapay.com
* Explorer: https://plasmadlt.com/monitor 
* Git: https://github.com/plasmadlt
* Docker: https://hub.docker.com/r/plasmachain/ion.cdt 
* Chain API: https://developer.plasmapay.com/chain.html 
 
 





The main difference **NTT** (Non-Transferable Tokens) is a special type of property
which works on the basic principles of NFT, but cannot be transferred to another owner after the transfer of ownership and is assigned to the account.

The two most likely use cases for non-transferable NTT tokens are:

* Certificates addressed to a particular account and cannot be transferred by this account to another.
* Licenses that can be granted to an account but not transferred.
* Prizes and rewards assigned to a particular account without the possibility of transferring to another account.

---------------------------
# Protocol Applicability

## Games

The use of NFT and NTT tokens simplifies the creation and makes ownership safe for unique characters and game items where the player can own, sell and exchange assets between other players and services. Within the blockchain, this allows you to instantly show that each side has the means at hand, while at the same time ensuring that the transfer of property rights belongs to this unique token with which the seller shares visibility on the blockchain. In-game resources - such as tokens or gold - are interchangeable, but some rare high-level items, perhaps the legendary sword or vehicle, may not be interchangeable.

## Collectibles

The NFT and NTT standards are intended for use for virtual assets, but also available for tangible assets that require transparent cryptography ownership, digital exchange and bidding.

## Licensing
Using NFT and NTT tokens can reduce piracy and allow people to sell their license on the open market for profit. Thus, users can also avoid annual subscriptions, use the software against a purchased license, and after use sell it to someone else. The license in this case acts as an asset for users.


---------------------------

# Contract actions

```
 regauthor		(name author, data, stemplate, string imgpriority)
 authorupdate		(author, data, stemplate, string imgpriority)


 # -- For Non-Fungible Tokens (NFT)---

 create			(author, category, owner, idata, mdata, requireсlaim)
 update			(author, owner, assetid, mdata)
 transfer		(from, to , [assetid1,..,assetidn], memo)
 burn			(owner, [assetid1,..,assetidn], memo)

 offer			(owner, newowner, [assetid1,..,assetidn], memo)
 canceloffer		(owner, [assetid1,..,assetidn])
 claim			(claimer, [assetid1,..,assetidn])

 delegate		(owner, to, [assetid1,..,assetidn], period, memo)
 undelegate		(owner, from, [assetid1,..,assetidn])
 delegatemore		(owner, assetid, period)

 attach			(owner, assetidc, [assetid1,..,assetidn])
 detach			(owner, assetidc, [assetid1,..,assetidn])

 attachf		(owner, author, quantity, assetidc)
 detachf		(owner, author, quantity, assetidc)


 # -- For Non-Transferable Tokens (NTT) ---

 createntt		(author, category, owner, idata, mdata, requireсlaim)
 updatentt		(author, owner, assetid, mdata)
 burnntt		(owner, [assetid1,..,assetidn], memo)
 claimntt		(claimer, [assetid1,..,assetidn])

```



---------------------------

# Contracts Structures
Most of the asset information goes into json idata and mdata string fields. idata stands for immutable data. This cannot be changed. mdata stands for mutable data and consists of fields that the resource author can update.

**Basic architecture** The asset has both volatile and non-volatile data.
**Owners**, not the author of the asset, have 100% control over transfers, lending / borrowing, and burning.
**Unique identifiers**, categories. NFT token can be filled with data according to the example, ID, Weapon, Gun, strength, speed, etc.
**Adding content** (url, img, webgl, mp3, video, hide): Adding visual content.
**Lending** (transfer to temporary possession). The owner can return the deferred asset instantly if the conditions

## Assets options 
```
sasset {
	uint64_t	id; 		// asset id used for transfer and search;
	name		owner;  	// asset owner;
	name		author;		// asset author (gameplay contract);
	name		category;	// asset category, chosen by author, immutable;
	string		idata;		// immutable assets data. Can be stringified JSON or just sha256 string;
	string		mdata;		// mutable assets data, added on creation or asset update by author. Can be
					// stringified JSON or just sha256 string;
	sasset[]	container;	// other NFTs attached to this asset
}
```

## Offers options
```
offers {
	uint64_t	assetid;	// asset id offered for claim ;
	name		owner;		// asset owner;
	name		offeredto;	// who can claim this asset ;
	uint64_t	cdate;		// offer create date;
}
```

## Authors options  
```
authors {
	name	author;			// assets author, who will be able to create and update assets;

	string	data;			// author’s data (json) will be used by markets for better display;
					// recommendations: logo, info, url;

	string	stemplate;		// data (json) schema to tell third-party markets how to display each NFT field.
					// key: state values, where key is the key from mdata or idata;
					// recommended values:
					// txt    | default type
					// url    | show as clickable URL
					// img    | link to img file
					// webgl  | link to webgl file
					// mp3    | link to mp3 file
					// video  | link to video file
					// hide   | do not show
					// imgb   | image as string in binary format
					// webglb | webgl binary
					// mp3b   | mp3 binary
					// videob | video binary

	string	imgpriority;		// Specifies primary image field for categories of NFT.
					//
					// This is used when you want your NFT primary image to be something other
					// than a URL to an image field specified in the field img.  It also allows you to
					// create categories of NFT with different primary image fields.
					//
					// data is a strigified json.
					// key: NFT categories.
					// value: a field from idata or mdata to be used as the primary image for
					// all NFT of that category.

}
```

## Lending 
Transfer to temporary possession (Delegate) 
```
delegates{
	uint64_t	assetid;	// asset id offered for claim;
	name		owner;		// asset owner;
	name		delegatedto;	// who can claim this asset;
	uint64_t	cdate;		// offer create date;
	uint64_t	period;		// Time in seconds that the asset will be lent. Lender cannot undelegate until
					// the period expires, however the receiver can transfer back at any time.
	string		memo;		// memo from action parameters. Max 64 length.

}
```

```
offerfs {
	uint64_t	id;		// id of the offer for claim (increments automatically)
	name		author;		// ft author
	name		owner;		// ft owner
	asset		quantity;	// quantity
	name		offeredto;	// account which can claim the offer
	uint64_t	cdate;		// offer creation date
}
```


## NTT asset options
```
sntnontokens555 {
	uint64_t	id; 		// NTT id used for claim or burn;
	name		owner;  	// asset owner (mutable - by owner!!!);
	name		author;		// asset author (game contract, immutable);
	name		category;	// asset category, chosen by author, immutable;
	string		idata;		// immutable assets data. Can be stringified JSON or just sha256 string;
	string		mdata;		// mutable assets data, added on creation or asset update by author. Can be
					// stringified JSON or just sha256 string;
}
```

```
nttoffers {
	uint64_t	id;		// id of the offer for claim (increments automatically)
	name		author;		// ft author
	name		owner;		// ft owner
	asset		quantity;	// quantity
	name		offeredto;	// account who can claim the offer
	uint64_t	cdate;		// offer creation date
}
```

# Examples: sol interface NFT assets

## Setup 

***Warning***
These examples work on the basis of the ionode interface, using tools **PLK** **SOL** that allow you to connect to the mainet network through a local terminal.  Install from [PlasmaDLT DevToolkit](https://github.com/plasmadlt/PlasmaDLT-devtoolkit)
 * **SOL** - is a command line tool that interfaces with the REST API exposed by ionode.
 * **PLK** - used to store private keys that **SOL** will use to sign transactions sent to the block chain.
 * sol --url http://swisubs.liberty.plasmadlt.com  -  Plasma P2P node address on [PlasmaDLT explorer](https://https://plasmadlt.com/monitor)
 *  --wallet-url http://0.0.0.0:9999 - your personal IP adress for PLK wallet.


### Build Contract 

Install and follow instructions   [PlasmaDLT DevToolkit](https://github.com/plasmadlt/PlasmaDLT-devtoolkit)

```
docker run -it --entrypoint /contacts/build.sh -v <contract source folder>:/contacts  plasmachain/ion.cdt:latest
```

### Deploy Contract 

Create your account name for contracts,  you need create account on Plasmapay and activate wallet  [PlasmaPay](https://plasmapay.com/)

```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 set contract nontokens555 /host-share/nontokens555
```
***Warning*** One account = one account contract

### Issue a asset that immediately receives the owner
// ACTION create( name author, name category, name owner, string idata, string mdata, bool requireclaim );

```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 create '{"author": "nontokens555", "category": "pokercards", "owner": "pldlt223aaaa", "idata": "QueenOfSpades", "mdata": "Mutable token data", "requireclaim": false}' -p nontokens555@active
# executed transaction: a2bfeb495e10fa7eab843cd4f03f75e95450cc112f3111094a6e70b1fb2a7ce4  200 bytes  508 us
# #       nontokens555 <= nontokens555::create              {"author":"nontokens555","category":"pokercards","owner":"pldlt223aaaa","idata":"QueenOfSpades","mdata":"...
# #  pldlt223aaaa <= nontokens555::create              {"author":"nontokens555","category":"pokercards","owner":"pldlt223aaaa","idata":"QueenOfSpades","mdata":"...
# #       nontokens555 <= nontokens555::createlog           {"author":"nontokens555","category":"pokercards","owner":"pldlt223aaaa","idata":"QueenOfSpades","mdata":"...
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Checking the action results
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 offers
# {
#   "rows": [],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 sassets
# {
#   "rows": [],
#   "more": false
# }
```

### Check Asset Owner
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223aaaa sassets
# {
#   "rows": [{
#       "id": "100000000000002",
#       "owner": "pldlt223aaaa",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```

### We issue a asset that receives the owner after claim
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 create '{"author": "nontokens555", "category": "pokercards", "owner": "pldlt223aaaa", "idata": "AceOfSpades", "mdata": "Mutable token data", "requireclaim": true}' -p nontokens555@active
# executed transaction: b80925d86c1e13355b669e52b252911df910b0391166a73c23174a798e05a6c8  192 bytes  1996 us
# #       nontokens555 <= nontokens555::create              {"author":"nontokens555","category":"pokercards","owner":"pldlt223aaaa","idata":"AceOfSpades","mdata":"Mu...
# #  pldlt223aaaa <= nontokens555::create              {"author":"nontokens555","category":"pokercards","owner":"pldlt223aaaa","idata":"AceOfSpades","mdata":"Mu...
# #       nontokens555 <= nontokens555::createlog           {"author":"nontokens555","category":"pokercards","owner":"pldlt223aaaa","idata":"AceOfSpades","mdata":"Mu...
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
### Check issue
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 offers
# {
#   "rows": [{
#       "assetid": "100000000000003",
#       "owner": "nontokens555",
#       "offeredto": "pldlt223aaaa",
#       "cdate": 1575974130
#     }
#   ],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 sassets
# {
#   "rows": [{
#       "id": "100000000000003",
#       "owner": "nontokens555",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "AceOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223aaaa sassets
# {
#   "rows": [{
#       "id": "100000000000002",
#       "owner": "pldlt223aaaa",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```

### Check the assets request
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 claim '{"claimer": "pldlt223aaaa", "assetids": [100000000000003]}' -p pldlt223aaaa@active
# executed transaction: 8de01dcf30433eff031b1cc5ef9962c24225c9c8fee9c2b46e4226143e0fcbf9  160 bytes  1705 us
# #       nontokens555 <= nontokens555::claim               {"claimer":"pldlt223aaaa","assetids":["100000000000003"]}
# #  pldlt223aaaa <= nontokens555::claim               {"claimer":"pldlt223aaaa","assetids":["100000000000003"]}
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
### Checking the status of tables
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 offers
# {
#   "rows": [],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223aaaa sassets
# {
#   "rows": [{
#       "id": "100000000000002",
#       "owner": "pldlt223aaaa",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     },{
#       "id": "100000000000003",
#       "owner": "pldlt223aaaa",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "AceOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```
### Checking the operation of the transfer action
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 transfer '{"from": "pldlt223aaaa", "to": "pldlt223bbbb", "assetids": [100000000000003], "memo": "Test transfer pldlt-179"}' -p pldlt223aaaa@active
# executed transaction: 7b8adad0cff3b2bb4c97d28a19e6293b72cf2405f1030976891a0dad9bfa28bd  192 bytes  1712 us
# #       nontokens555 <= nontokens555::transfer            {"from":"pldlt223aaaa","to":"pldlt223bbbb","assetids":["100000000000003"],"memo":"Test transfer pldl...
# #  pldlt223aaaa <= nontokens555::transfer            {"from":"pldlt223aaaa","to":"pldlt223bbbb","assetids":["100000000000003"],"memo":"Test transfer pldl...
# #  pldlt223bbbb <= nontokens555::transfer            {"from":"pldlt223aaaa","to":"pldlt223bbbb","assetids":["100000000000003"],"memo":"Test transfer pldl...
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223aaaa sassets
# {
#   "rows": [{
#       "id": "100000000000002",
#       "owner": "pldlt223aaaa",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223bbbb sassets
# {
#   "rows": [{
#       "id": "100000000000003",
#       "owner": "pldlt223bbbb",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "AceOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```

### Testing offer/canceloffer
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 offer '{ "owner": "pldlt223aaaa", "newowner": "pldlt223bbbb", "assetids": [100000000000002], "memo": "Offer 100000000000002 token to pldlt223bbbb account" }' -p pldlt223aaaa@active
# executed transaction: 78372e3e7875f522a7a157f5251d4a3c0a0d2d071cd1cddf1c066175cee2fc96  176 bytes  671 us
# #       nontokens555 <= nontokens555::offer               {"owner":"pldlt223aaaa","newowner":"pldlt223bbbb","assetids":["100000000000002"],"memo":"Offer 10000...
# #  pldlt223aaaa <= nontokens555::offer               {"owner":"pldlt223aaaa","newowner":"pldlt223bbbb","assetids":["100000000000002"],"memo":"Offer 10000...
# #  pldlt223bbbb <= nontokens555::offer               {"owner":"pldlt223aaaa","newowner":"pldlt223bbbb","assetids":["100000000000002"],"memo":"Offer 10000...
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 offers
# {
#   "rows": [{
#       "assetid": "100000000000002",
#       "owner": "pldlt223aaaa",
#       "offeredto": "pldlt223bbbb",
#       "cdate": 1575988898
#     }
#   ],
#   "more": false
# }
```

### Сheck canceloffer
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 canceloffer '{"owner": "pldlt223aaaa", "assetids": [100000000000002]}' -p pldlt223aaaa@active
# executed transaction: 22ea53882d8d9cdd54280e9fab182b586222a3f388c98b5b66e314c8cb42661b  112 bytes  208 us
# #       nontokens555 <= nontokens555::canceloffer         {"owner":"pldlt223aaaa","assetids":["100000000000002"]}
# #  pldlt223aaaa <= nontokens555::canceloffer         {"owner":"pldlt223aaaa","assetids":["100000000000002"]}
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 offers
# {
#   "rows": [],
#   "more": false
# }
```
### Check  claim
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 offer '{ "owner": "pldlt223aaaa", "newowner": "pldlt223bbbb", "assetids": [100000000000002], "memo": "Offer 100000000000002 token to pldlt223bbbb account" }' -p pldlt223aaaa@active

# ACTION
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com --wallet-url http://0.0.0.0:9999 push action nontokens555 claim '{"claimer": "pldlt223bbbb", "assetids": [100000000000002] }' -p pldlt223bbbb@active
# executed transaction: 8fdb428d5674b3e5d386ba972fe73024f1ca634ba2623697696ed467221f1919  160 bytes  473 us
# #       nontokens555 <= nontokens555::claim               {"claimer":"pldlt223bbbb","assetids":["100000000000002"]}
# #  pldlt223bbbb <= nontokens555::claim               {"claimer":"pldlt223bbbb","assetids":["100000000000002"]}
# warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 nontokens555 offers
# {
#   "rows": [],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223bbbb sassets
# {
#   "rows": [{
#       "id": "100000000000002",
#       "owner": "pldlt223bbbb",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     },{
#       "id": "100000000000003",
#       "owner": "pldlt223bbbb",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "AceOfSpades",
#       "mdata": "Mutable token data",
#       "containerf": []
#     }
#   ],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://swisubs.liberty.plasmadlt.com get table nontokens555 pldlt223aaaa sassets
# {
#   "rows": [],
#   "more": false
# }
```



-----------------

# Examples: sol interface NТT assets

## Create a Non transferable token - a card of Queen of Hearts.
createntt ( author, category, owner, idata, mdata, requireclaim); pldlt223aaaa, pldlt223bbbb
```
docker exec -i <network> sol --url http://127.0.0.1:8800 --wallet-url http://127.0.0.1:8799 push action nontokens555 createntt '{"author": "nontokens555", "category": "pokercards", "owner": "pldlt223aaaa", "idata": "QueenOfSpades", "mdata": "mutable data", "requireclaim": true }' -p  nontokens555@active
```
### Check the result of creating this asset, the author’s account is still the owner of the asset - nontokens555
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 nontokens555 snttassets
# {
#   "rows": [{
#       "id": "100000000000001",
#       "owner": "nontokens555",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "mutable data"
#     }
#   ],
#   "more": false
# }
```
### Check the table of offers, there is a token offer for the account pldlt223aaaa
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 nontokens555 nttoffers
# {
#   "rows": [{
#       "assetid": "100000000000001",
#       "owner": "nontokens555",
#       "offeredto": "pldlt223aaaa",
#       "cdate": 1575966424
#     }
#   ],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 pldlt223aaaa snttassets
```
### Check how the account pldlt223aaaa requests a asset in its possession
void nontokens555::claimntt( name claimer, std::vector<uint64_t>& assetids )
```
docker exec -i <network> sol --url http://127.0.0.1:8800 --wallet-url http://127.0.0.1:8799 push action nontokens555 claimntt '{"claimer": "pldlt223aaaa", "assetids": ["100000000000001"]}' -p pldlt223aaaa@active
# executed transaction: 33915f1015d0402420bf5337ed1c8973b449c052d54379a82c7730f61216bd7a  112 bytes  7392 us
# #       nontokens555 <= nontokens555::claimntt            {"claimer":"pldlt223aaaa","assetids":["100000000000001"]}
# #  pldlt223aaaa <= nontokens555::claimntt            {"claimer":"pldlt223aaaa","assetids":["100000000000001"]}
# warning: transaction executed locally, but may not be confirmed by the network yet         ] 
```
### Check the result of the asset transfer to account ownership pldlt223aaaa
  nontokens555 account no longer owns a token
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 nontokens555 snttassets
# {
#   "rows": [],
#   "more": false
# }
```
### Check asset holder account pldlt223aaaa
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 pldlt223aaaa snttassets
# {
#   "rows": [{
#       "id": "100000000000001",
#       "owner": "pldlt223aaaa",
#       "author": "nontokens555",
#       "category": "pokercards",
#       "idata": "QueenOfSpades",
#       "mdata": "mutable data"
#     }
#   ],
#   "more": false
# }
```
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 nontokens555 nttoffers
# {
#   "rows": [],
#   "more": false
# }
```
### Check the operation of the asset burn
```
# ACTION burnntt( name owner, std::vector< uint64_t >& assetids, string memo );
docker exec -i <network> sol --url http://127.0.0.1:8800 --wallet-url http://127.0.0.1:8799 push action nontokens555 burnntt '{"owner": "pldlt223aaaa", "assetids": ["100000000000001"], "memo": "Burn queen of spades"}' -p pldlt223aaaa@active
# executed transaction: e5a751b63b55bb8758c01f457700826d410fab8994941ef4f07e7facdc9101bf  136 bytes  357 us
# #       nontokens555 <= nontokens555::burnntt             {"owner":"pldlt223aaaa","assetids":["100000000000001"],"memo":"Burn queen of spades"}
# #  pldlt223aaaa <= nontokens555::burnntt             {"owner":"pldlt223aaaa","assetids":["100000000000001"],"memo":"Burn queen of spades"}
# warning: transaction executed locally, but may not be confirmed by the network yet         ] 
```
### Check the results of the action - burned to the ground.
```
docker exec -i <network> sol --url http://127.0.0.1:8800 get table nontokens555 pldlt223aaaa snttassets
# {
#   "rows": [],
#   "more": false
# }
```


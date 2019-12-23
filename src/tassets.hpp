#pragma once
/*
 * @section DESCRIPTION
 * tassets - its example name can change
 *
 * NTT and NFT tokens 
 */

#include <ion/ion.hpp>
#include <ion/asset.hpp>
#include <ion/singleton.hpp>
#include <ion/transaction.hpp>

using namespace ion;
using std::string;

CONTRACT tassets : public contract
{
public:
	using contract::contract;


	ACTION updatever( string version );
	using updatever_action = action_wrapper< "updatever"_n, &tassets::updatever >;


	ACTION regauthor( name author, string data, string stemplate, string imgpriority );
	using regauthor_action = action_wrapper< "regauthor"_n, &tassets::regauthor >;


	ACTION authorupdate( name author, string data, string stemplate, string imgpriority );
	using authorupdate_action = action_wrapper< "authorupdate"_n, &tassets::authorupdate >;


	ACTION create( name author, name category, name owner, string idata, string mdata, bool requireclaim );
	using create_action = action_wrapper< "create"_n, &tassets::create >;


	ACTION claim( name claimer, std::vector< uint64_t >& assetids );
	using claim_action = action_wrapper< "claim"_n, &tassets::claim >;


	ACTION transfer( name from, name to, std::vector< uint64_t >& assetids, string memo );
	using transfer_action = action_wrapper< "transfer"_n, &tassets::transfer >;


	ACTION update( name author, name owner, uint64_t assetid, string mdata );
	using update_action = action_wrapper< "update"_n, &tassets::update >;


	ACTION offer( name owner, name newowner, std::vector< uint64_t >& assetids, string memo );
	using offer_action = action_wrapper< "offer"_n, &tassets::offer >;


	ACTION canceloffer( name owner, std::vector<uint64_t>& assetids );
	using canceloffer_action = action_wrapper< "canceloffer"_n, &tassets::canceloffer >;


	ACTION burn( name owner, std::vector< uint64_t >& assetids, string memo );
	using burn_action = action_wrapper< "burn"_n, &tassets::burn >;


	ACTION delegate( name owner, name to, std::vector< uint64_t >& assetids, uint64_t period, string memo );
	using delegate_action = action_wrapper< "delegate"_n, &tassets::delegate >;


	ACTION undelegate( name owner, name from, std::vector< uint64_t >& assetids );
	using undelegate_action = action_wrapper< "undelegate"_n, &tassets::undelegate >;


	ACTION attach( name owner, uint64_t assetidc, std::vector< uint64_t >& assetids );
	using attach_action = action_wrapper< "attach"_n, &tassets::attach >;


	ACTION detach( name owner, uint64_t assetidc, std::vector< uint64_t >& assetids );
	using detach_t_action = action_wrapper< "detach"_n, &tassets::detach >;


	ACTION delegatemore( name owner, uint64_t assetidc, uint64_t period );
	using delegatemore_action = action_wrapper< "delegatemore"_n, &tassets::delegatemore >;


	ACTION attachf( name owner, name author, asset quantity, uint64_t assetidc );
	using attachf_t_action = action_wrapper< "attachf"_n, &tassets::attachf >;


	ACTION detachf( name owner, name author, asset quantity, uint64_t assetidc );
	using detachf_t_action = action_wrapper< "detachf"_n, &tassets::detachf >;

	ACTION createf( name author, asset maximum_supply, bool authorctrl, string data );
	using createf_action = action_wrapper< "createf"_n, &tassets::createf >;


	ACTION updatef( name author, symbol sym, string data );
	using updatef_action = action_wrapper< "updatef"_n, &tassets::updatef >;


	ACTION issuef( name to, name author, asset quantity, string memo );
	using issuef_action = action_wrapper< "issuef"_n, &tassets::issuef >;


	ACTION transferf( name from, name to, name author, asset quantity, string memo );
	using transferf_action = action_wrapper< "transferf"_n, &tassets::transferf >;



	ACTION offerf( name owner, name newowner, name author, asset quantity, string memo );
	using offerf_action = action_wrapper< "offerf"_n, &tassets::offerf >;



	ACTION cancelofferf( name owner, std::vector< uint64_t >& ftofferids );
	using cancelofferf_action = action_wrapper< "cancelofferf"_n, &tassets::cancelofferf >;


	ACTION claimf( name claimer, std::vector< uint64_t >& ftofferids );
	using claimf_action = action_wrapper< "claimf"_n, &tassets::claimf >;


	ACTION burnf( name from, name author, asset quantity, string memo );
	using burnf_action = action_wrapper< "burnf"_n, &tassets::burnf >;


	ACTION openf( name owner, name author, const symbol& symbol, name ram_payer );
	using openf_action = action_wrapper< "openf"_n, &tassets::openf >;


	ACTION closef( name owner, name author, const symbol& symbol );
	using closef_action = action_wrapper< "closef"_n, &tassets::closef >;


	static asset get_supply( name token_contract_account, name author, symbol_code sym_code );


	static asset get_balance( name token_contract_account, name owner, name author, symbol_code sym_code );


	ACTION createntt ( name author, name category, name owner, string idata, string mdata, bool requireclaim );
	using createntt_action = action_wrapper< "createntt"_n, &tassets::createntt >;


	ACTION createnttlog( name author, name category, name owner, string idata, string mdata, uint64_t assetid, bool requireclaim );
	using createnttlog_action = action_wrapper< "createnttlog"_n, &tassets::createnttlog >;


	ACTION claimntt( name claimer, std::vector< uint64_t >& assetids );
	using claimntt_action = action_wrapper< "claimntt"_n, &tassets::claimntt >;


	ACTION updatentt( name author, name owner, uint64_t assetid, string mdata );
	using updatentt_action = action_wrapper< "updatentt"_n, &tassets::updatentt >;


	ACTION burnntt( name owner, std::vector< uint64_t >& assetids, string memo );
	using burnntt_action = action_wrapper< "burnntt"_n, &tassets::burnntt >;

private:

	uint64_t getid( bool defer = false );


	uint64_t getFTIndex( name author, symbol symbol );
	void attachdeatch( name owner, name author, asset quantity, uint64_t assetidc, bool attach );
	void sub_balancef( name owner, name author, asset value );
	void add_balancef( name owner, name author, asset value, name ram_payer );

	template<typename... Args>
	void sendEvent( name author, name rampayer, name seaction, const std::tuple<Args...> &tup );


	TABLE sauthor {
		name			author;
		string			data;
		string			stemplate;
		string			imgpriority;

		auto primary_key() const {
			return author.value;
		}

	};
	typedef ion::multi_index< "authors"_n, sauthor > authors;

	TABLE currency_stats {
		asset		supply;
		asset		max_supply;
		name		issuer;
		uint64_t 	id;
		bool		authorctrl;
		string		data;

		uint64_t primary_key()const {
			return supply.symbol.code().raw();
		}
	};
	typedef ion::multi_index< "stat"_n, currency_stats > stats;

	TABLE account {
		uint64_t	id;
		name		author;
		asset		balance;

		uint64_t primary_key()const {
			return id;
		}
	};

	typedef ion::multi_index< "accounts"_n, account > accounts;


	TABLE sasset {
		uint64_t                id;
		name                    owner;
		name                    author;
		name                    category;
		string                  idata; // immutable data
		string                  mdata; // mutable data
		std::vector<sasset>     container;
		std::vector<account>    containerf;

		auto primary_key() const {
			return id;
		}
		uint64_t by_author() const {
			return author.value;
		}

	};
	typedef ion::multi_index< "sassets"_n, sasset,
		ion::indexed_by< "author"_n, ion::const_mem_fun<sasset, uint64_t, &sasset::by_author> >
		> sassets;


	TABLE snttasset {
		uint64_t                id;
		name                    owner;
		name                    author;
		name                    category;
		string                  idata; // immutable data
		string                  mdata; // mutable data

		auto primary_key() const {
			return id;
		}
		uint64_t by_author() const {
			return author.value;
		}

	};
	typedef ion::multi_index< "snttassets"_n, snttasset,
		ion::indexed_by< "author"_n, ion::const_mem_fun<snttasset, uint64_t, &snttasset::by_author> >
		> snttassets;


	TABLE soffer {
		uint64_t		assetid;
		name			owner;
		name			offeredto;
		uint64_t		cdate;

		auto primary_key() const {
			return assetid;
		}
		uint64_t by_owner() const {
			return owner.value;
		}
		uint64_t by_offeredto() const {
			return offeredto.value;
		}
	};
	typedef ion::multi_index< "offers"_n, soffer,
		ion::indexed_by< "owner"_n, ion::const_mem_fun< soffer, uint64_t, &soffer::by_owner > >,
		ion::indexed_by< "offeredto"_n, ion::const_mem_fun< soffer, uint64_t, &soffer::by_offeredto > >
		> offers;


	TABLE sofferf {
		uint64_t		id;
		name			author;
		name			owner;
		asset			quantity;
		name			offeredto;
		uint64_t		cdate;

		auto primary_key() const {
			return id;
		}
		uint64_t by_owner() const {
			return owner.value;
		}
		uint64_t by_offeredto() const {
			return offeredto.value;
		}
	};
	typedef ion::multi_index< "offerfs"_n, sofferf,
		ion::indexed_by< "owner"_n, ion::const_mem_fun< sofferf, uint64_t, &sofferf::by_owner > >,
		ion::indexed_by< "offeredto"_n, ion::const_mem_fun< sofferf, uint64_t, &sofferf::by_offeredto > >
		> offerfs;


	TABLE snttoffer {
		uint64_t		assetid;
		name			owner;
		name			offeredto;
		uint64_t		cdate;

		auto primary_key() const {
			return assetid;
		}
		uint64_t by_owner() const {
			return owner.value;
		}
		uint64_t by_offeredto() const {
			return offeredto.value;
		}
	};
	typedef ion::multi_index< "nttoffers"_n, snttoffer,
		ion::indexed_by< "owner"_n, ion::const_mem_fun< snttoffer, uint64_t, &snttoffer::by_owner > >,
		ion::indexed_by< "offeredto"_n, ion::const_mem_fun< snttoffer, uint64_t, &snttoffer::by_offeredto > >
		> nttoffers;


	TABLE sdelegate {
		uint64_t		assetid;
		name			owner;
		name			delegatedto;
		uint64_t		cdate;
		uint64_t		period;
		string			memo;

		auto primary_key() const {
			return assetid;
		}
		uint64_t by_owner() const {
			return owner.value;
		}
		uint64_t by_delegatedto() const {
			return delegatedto.value;
		}
	};
	typedef ion::multi_index< "delegates"_n, sdelegate,
		ion::indexed_by< "owner"_n, ion::const_mem_fun< sdelegate, uint64_t, &sdelegate::by_owner > >,
		ion::indexed_by< "delegatedto"_n, ion::const_mem_fun< sdelegate, uint64_t, &sdelegate::by_delegatedto > >
	> delegates;


	TABLE global {
		global() {}
		uint64_t lnftid = 100000000000000;
		uint64_t defid = 1000000;
		uint64_t spare1 = 0;
		uint64_t spare2 = 0;

		IONLIB_SERIALIZE( global, ( lnftid )( defid )( spare1 )( spare2 ) )
	};

	typedef ion::singleton< "global"_n, global > conf; /// singleton
	global _cstate; /// global state


	TABLE tokenconfigs {
		name			standard;
		std::string		version;
	};
	typedef singleton< "tokenconfigs"_n, tokenconfigs > Configs;
};

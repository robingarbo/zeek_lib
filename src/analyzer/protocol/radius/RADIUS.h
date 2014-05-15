// Generated by binpac_quickstart

#ifndef ANALYZER_PROTOCOL_RADIUS_RADIUS_H
#define ANALYZER_PROTOCOL_RADIUS_RADIUS_H

#include "events.bif.h"


#include "analyzer/protocol/udp/UDP.h"

#include "radius_pac.h"

namespace analyzer { namespace RADIUS {

class RADIUS_Analyzer

: public analyzer::Analyzer {

public:
	RADIUS_Analyzer(Connection* conn);
	virtual ~RADIUS_Analyzer();

	// Overriden from Analyzer.
	virtual void Done();
	
	virtual void DeliverPacket(int len, const u_char* data, bool orig,
					uint64 seq, const IP_Hdr* ip, int caplen);
	

	static analyzer::Analyzer* InstantiateAnalyzer(Connection* conn)
		{ return new RADIUS_Analyzer(conn); }

	static bool Available()
		{
		return ( radius_message );
		}

protected:
	binpac::RADIUS::RADIUS_Conn* interp;
	
};

} } // namespace analyzer::* 

#endif

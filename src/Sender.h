/*
 * Sender.h
 *
 *  Created on: Mar 5, 2014
 \*      Author: Jonas Kunze (kunze.jonas@gmail.com)
 */

#ifndef SENDER_H_
#define SENDER_H_

#include <boost/asio/ip/udp.hpp>
#include <sys/types.h>
#include <utils/AExecutable.h>
#include <cstdint>

namespace na62 {

class Sender: public AExecutable {
public:
	Sender(uint sourceID, uint numberOfTelBoards, uint numberOfMEPsPerBurst, uint autoburst, uint timebased);
	virtual ~Sender();
	int net_bind_udp();
	inline uint getSentData() {
		return sentData_;
	}
	inline uint64_t getSentFrames() {
		return num_mens_;
	}

	inline double getFrec() {
		return frec_;
	}

	inline void setSentDataToZero(){
		sentData_ = 0;
	}

private:
	uint sourceID_;
	uint numberOfTelBoards_;
	uint numberOfMEPsPerBurst_;
	uint eventLength_;
	uint durationSeconds_;
	uint burstNum_;
	uint sentData_;
	uint autoburst_;
	uint timebased_;
	boost::posix_time::ptime start_;
	//std::atomic<uint64_t> num_mens_;
	//std::atomic<double> frec_;
	uint32_t num_mens_;
	double frec_;
	uint rateL0_;
	uint optRateL0_;
	uint32_t myIP_;

	boost::asio::io_service io_service_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint receiver_endpoint_;

	void thread();

	void sendMEPs(uint8_t sourceID, uint tel62Num);
	uint16_t sendMEP(char* buffer, uint32_t firstEventNum,
			const unsigned short eventsPerMEP, uint& randomLength,
			char* randomData, bool isLastMEPOfBurst);


};

} /* namespace na62 */

#endif /* SENDER_H_ */

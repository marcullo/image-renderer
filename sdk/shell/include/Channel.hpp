#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <mqueue.h>

#include <string>

namespace sdk::channel {

class Channel {
public:
	/** The direction of communication which specifies the required roles of the transmission. */
	enum class Direction {
		MOSI, /** Master can only send, slave can only receive. */
		MISO, /** Master can only receive, slave can only send. */
	};

	/** Setup one-directional communication channel. */
	Channel(const char* label, bool master, Direction direction);

	/** Do not setup a channel without given arguments. */
	Channel() = delete;

	/** Destruct the object taking care of message queue resources. */
	~Channel();

	/** Send message if you are allowed to. */
	void send(const std::string& message);

	/** Receive message. */
	std::string receive();

protected:
	static const long msg_size = 100; /** Maximal message length. */
	static const long max_msgs = 10; /** Message slots in a msg queue. */
	static const int pmode = 0655; /** Mode of dealing with msg queue. */

	bool master; /** Is channel object run by master? */
	Direction dir; /** Direction of communication. */
	struct mq_attr attr; /** Message queue attributes. */
	char label[10]; /** Message queue label. */
	char user[10]; /** Name of channel object user. */
};

class ChannelMOSI : public Channel {
public:
	ChannelMOSI(bool master) : Channel("/mq_mosi", master, Direction::MOSI) {}
};

class ChannelMISO : public Channel {
public:
	ChannelMISO(bool master) : Channel("/mq_miso", master, Direction::MISO) {}
};

} // namespace sdk::channel

#endif // CHANNEL_HPP

#include "Channel.hpp"

#include <fcntl.h>
#include <sys/wait.h>

#include <cstring>
#include <iostream>

#include "log_settings.hpp"
#define LOG_LEVEL LOG_LEVEL__CHANNEL
#define LOG_LEVEL_MODULE_NAME "channel"
#include "logging.hpp"

namespace sdk::channel {

Channel::Channel(const char* l, bool m, Direction direction) :
	master(m),
	dir(direction)
{
	sprintf(this->label, "%s", l);
	sprintf(this->user, "%s", this->master ? "master": "slave");
	this->attr.mq_curmsgs = 0;
	this->attr.mq_flags = 0;
	this->attr.mq_msgsize = Channel::msg_size;
	this->attr.mq_maxmsg = Channel::max_msgs;
}

Channel::~Channel()
{
	if (this->master) {
		mq_unlink(this->label);
	}
}

void Channel::send(const std::string& message)
{
	if (this->master && this->dir == Direction::MISO) {
		ERR("%s: you can send to MOSI, not MISO!", this->user);
		return;
	}
	if (!this->master && this->dir == Direction::MOSI) {
		ERR("%s: you can send to MISO, not MOSI!", this->user);
		return;
	}

	mqd_t mq = mq_open(this->label, O_WRONLY|O_CREAT, Channel::pmode, &(this->attr));
	if(mq == -1) {
		ERR("%s: failed to mq_open", this->user);
		return;
	}

	const char* msg = message.c_str();
	int status = mq_send(mq, msg, strlen(msg) + 1, 0);
	if (status == -1) {
		ERR("%s: failed to mq_send", this->user);
		goto end;
	}

	DBG("by %s: %s", this->user, message.c_str());

end:
	mq_close(mq);
}

std::string Channel::receive()
{
	std::string message;

	if (this->master && this->dir == Direction::MOSI) {
		ERR("%s: you can receive with MISO, not MOSI!", this->user);
		return message;
	}
	if (!this->master && this->dir == Direction::MISO) {
		ERR("%s: you can receive with MOSI, not MISO!", this->user);
		return message;
	}

	mqd_t mq = mq_open(this->label, O_RDONLY|O_CREAT, Channel::pmode, &(this->attr));
	if(mq == -1) {
		ERR("%s: failed to mq_open", this->user);
		return message;
	}

	size_t size = Channel::msg_size;

	message.resize(size, 0);

	char* msg = &message.at(0);
	int status = mq_receive(mq, msg, size, 0);
	if (status == -1) {
		ERR("%s: failed to mq_receive", this->user);
		goto end;
	}

	DBG("by %s: %s", this->user, message.c_str());

end:
	mq_close(mq);

	return message;
}

} // namespace sdk::channel

#include "channel.h"

int main(int argc, char* argv[])
{
    char event_type;
    unsigned long period;
    pid_t pid;
    if(argc != 4 ||
        sscanf(argv[1], "%c", &event_type) != 1 ||
	sscanf(argv[2], "%lu", &period) != 1 ||
        sscanf(argv[3], "%d", &pid) != 1)
    {
        printf("USAGE: %s <event_type>(l for load, s for store) <period> <pid>\n", argv[0]);
        return 1;
    }

    if(event_type != 'l' || event_type != 's'){
    	printf("event type only support load or store\n");
    }

    Channel c;
    int ret;
    if(event_type == 'l')
	ret = c.bind(pid, Channel::CHANNEL_LOAD);
    else
	ret = c.bind(pid, Channel::CHANNEL_STORE);

    if(ret)
        return ret;
    ret = c.setPeriod(period);
    if(ret)
        return ret;
    while(true)
    {
        Channel::Sample sample;
        ret = c.readSample(&sample);
        if(ret == -EAGAIN)
        {
            usleep(10000);
            continue;
        }
        else if(ret < 0)
            return ret;
        else
            printf("type: %x, cpu: %u, pid: %u, tid: %u, address: 0x%lx\n",
                sample.type, sample.cpu, sample.pid, sample.tid, sample.address);
    }
    return 0;
}

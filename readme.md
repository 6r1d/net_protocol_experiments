# Net experiments
Goal: make a basic protocol to run commands on a server and get results
on a client using.

Note: those commands will be limited to a number of reliable ones later.

# Protocol (loose) definition

We need a new `UUID` for each command we request the server to execute.
Such UUIDs are marked as a `[label]`.

Each client / server packet contains a couple of header bytes to check if
those are correct.

## Typical request flow

    > run [command]
    < command acknowledged as [label]
    > status [label]
      < [label] is [done][output_size]
      < [label] is [being processed]
      < [label] is [timed out]
      < [label] is [failed][output_size]
    > read [label][start_byte][end_byte]
      < [output]
    > remove [label]
      < [status]

## Other commands

    > uptime
      < n.n seconds

## Articles to read

Since I'm using UDP, I need to guarantee a reliable data transmission.

 * There's a Stack Overflow [thread](https://stackoverflow.com/questions/43390361/) about that.
 * There's also a Wikipedia [article](https://en.wikipedia.org/wiki/UDP-based_Data_Transfer_Protocol) about the related protocol.

### Network protocol examples

 * LibDill network protocol [tutorial](http://libdill.org/tutorial-protocol.html) contains some parsing and handshake ideas.
 * An [article](https://www.saminiir.com/lets-code-tcp-ip-stack-4-tcp-data-flow-socket-api/) about TCP stack.
 * Linux userspace TCP/IP stack: [level-ip](https://github.com/saminiir/level-ip).

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

## Other commands to make

    > uptime
      < n.n seconds
    > ip
      < ip address

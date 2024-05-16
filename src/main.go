package main

import (
    "fmt"
    "net"
    "os"
    "bufio"
    "log"
)

func main(){
    log.SetPrefix("[-]\ttcprequest: ")
    log.SetFlags(0)

    if len(os.Args) < 2 {
        fmt.Printf("Usage: %v target_ip_address\n", os.Args[0])
        log.Fatal("Exception: missing target addr")
    }

    //connect target
    sock, err := net.Dial("tcp", os.Args[1])
    if nil != err {
        fmt.Println("Exception: ", err)
        log.Fatal("Exception: tcp bind failed.")
    }
    //send request
    fmt.Fprintf(sock, "HEAD / HTTP/1.0\r\n\r\n")
    status, err := bufio.NewReader(sock).ReadString('\n')
    if nil != err {
        fmt.Println("Exception: ", err)
        log.Fatal("Exception: tcp r/w failed.")
    }

    log.Print("Done.")

    //now parse request result
    //var http_code string
    fmt.Println(status)
}
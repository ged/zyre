/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
#ifndef Q_ZSOCK_H
#define Q_ZSOCK_H

#include "qzyre.h"

class QT_ZYRE_EXPORT QZsock : public QObject
{
    Q_OBJECT
public:

    //  Copy-construct to return the proper wrapped c types
    QZsock (zsock_t *self, QObject *qObjParent = 0);

    //  Create a new socket. Returns the new socket, or NULL if the new socket
    //  could not be created. Note that the symbol zsock_new (and other       
    //  constructors/destructors for zsock) are redirected to the *_checked   
    //  variant, enabling intelligent socket leak detection. This can have    
    //  performance implications if you use a LOT of sockets. To turn off this
    //  redirection behaviour, define ZSOCK_NOCHECK.                          
    explicit QZsock (int type, QObject *qObjParent = 0);

    //  Create a PUB socket. Default action is bind.
    static QZsock* newPub (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a SUB socket, and optionally subscribe to some prefix string. Default
    //  action is connect.                                                          
    static QZsock* newSub (const QString &endpoint, const QString &subscribe, QObject *qObjParent = 0);

    //  Create a REQ socket. Default action is connect.
    static QZsock* newReq (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a REP socket. Default action is bind.
    static QZsock* newRep (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a DEALER socket. Default action is connect.
    static QZsock* newDealer (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a ROUTER socket. Default action is bind.
    static QZsock* newRouter (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a PUSH socket. Default action is connect.
    static QZsock* newPush (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a PULL socket. Default action is bind.
    static QZsock* newPull (const QString &endpoint, QObject *qObjParent = 0);

    //  Create an XPUB socket. Default action is bind.
    static QZsock* newXpub (const QString &endpoint, QObject *qObjParent = 0);

    //  Create an XSUB socket. Default action is connect.
    static QZsock* newXsub (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a PAIR socket. Default action is connect.
    static QZsock* newPair (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a STREAM socket. Default action is connect.
    static QZsock* newStream (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a SERVER socket. Default action is bind.
    static QZsock* newServer (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a CLIENT socket. Default action is connect.
    static QZsock* newClient (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a RADIO socket. Default action is bind.
    static QZsock* newRadio (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a DISH socket. Default action is connect.
    static QZsock* newDish (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a GATHER socket. Default action is bind.
    static QZsock* newGather (const QString &endpoint, QObject *qObjParent = 0);

    //  Create a SCATTER socket. Default action is connect.
    static QZsock* newScatter (const QString &endpoint, QObject *qObjParent = 0);

    //  Destroy the socket. You must use this for any socket created via the
    //  zsock_new method.                                                   
    ~QZsock ();

    //  Bind a socket to a formatted endpoint. For tcp:// endpoints, supports   
    //  ephemeral ports, if you specify the port number as "*". By default      
    //  zsock uses the IANA designated range from C000 (49152) to FFFF (65535). 
    //  To override this range, follow the "*" with "[first-last]". Either or   
    //  both first and last may be empty. To bind to a random port within the   
    //  range, use "!" in place of "*".                                         
    //                                                                          
    //  Examples:                                                               
    //      tcp://127.0.0.1:*           bind to first free port from C000 up    
    //      tcp://127.0.0.1:!           bind to random port from C000 to FFFF   
    //      tcp://127.0.0.1:*[60000-]   bind to first free port from 60000 up   
    //      tcp://127.0.0.1:![-60000]   bind to random port from C000 to 60000  
    //      tcp://127.0.0.1:![55000-55999]                                      
    //                                  bind to random port from 55000 to 55999 
    //                                                                          
    //  On success, returns the actual port number used, for tcp:// endpoints,  
    //  and 0 for other transports. On failure, returns -1. Note that when using
    //  ephemeral ports, a port may be reused by different services without     
    //  clients being aware. Protocols that run on ephemeral ports should take  
    //  this into account.                                                      
    int bind (const QString &param);

    //  Returns last bound endpoint, if any.
    const QString endpoint ();

    //  Unbind a socket from a formatted endpoint.                     
    //  Returns 0 if OK, -1 if the endpoint was invalid or the function
    //  isn't supported.                                               
    int unbind (const QString &param);

    //  Connect a socket to a formatted endpoint        
    //  Returns 0 if OK, -1 if the endpoint was invalid.
    int connect (const QString &param);

    //  Disconnect a socket from a formatted endpoint                  
    //  Returns 0 if OK, -1 if the endpoint was invalid or the function
    //  isn't supported.                                               
    int disconnect (const QString &param);

    //  Attach a socket to zero or more endpoints. If endpoints is not null,     
    //  parses as list of ZeroMQ endpoints, separated by commas, and prefixed by 
    //  '@' (to bind the socket) or '>' (to connect the socket). Returns 0 if all
    //  endpoints were valid, or -1 if there was a syntax error. If the endpoint 
    //  does not start with '@' or '>', the serverish argument defines whether   
    //  it is used to bind (serverish = true) or connect (serverish = false).    
    int attach (const QString &endpoints, bool serverish);

    //  Returns socket type as printable constant string.
    const QString typeStr ();

    //  Send a 'picture' message to the socket (or actor). The picture is a   
    //  string that defines the type of each frame. This makes it easy to send
    //  a complex multiframe message in one call. The picture can contain any 
    //  of these characters, each corresponding to one or two arguments:      
    //                                                                        
    //      i = int (signed)                                                  
    //      1 = uint8_t                                                       
    //      2 = uint16_t                                                      
    //      4 = uint32_t                                                      
    //      8 = uint64_t                                                      
    //      s = char *                                                        
    //      b = byte *, size_t (2 arguments)                                  
    //      c = zchunk_t *                                                    
    //      f = zframe_t *                                                    
    //      h = zhashx_t *                                                    
    //      U = zuuid_t *                                                     
    //      p = void * (sends the pointer value, only meaningful over inproc) 
    //      m = zmsg_t * (sends all frames in the zmsg)                       
    //      z = sends zero-sized frame (0 arguments)                          
    //      u = uint (deprecated)                                             
    //                                                                        
    //  Note that s, b, c, and f are encoded the same way and the choice is   
    //  offered as a convenience to the sender, which may or may not already  
    //  have data in a zchunk or zframe. Does not change or take ownership of 
    //  any arguments. Returns 0 if successful, -1 if sending failed for any  
    //  reason.                                                               
    int send (const QString &picture,  ...);

    //  Send a 'picture' message to the socket (or actor). This is a va_list 
    //  version of zsock_send (), so please consult its documentation for the
    //  details.                                                             
    int vsend (const QString &picture, va_list argptr);

    //  Receive a 'picture' message to the socket (or actor). See zsock_send for
    //  the format and meaning of the picture. Returns the picture elements into
    //  a series of pointers as provided by the caller:                         
    //                                                                          
    //      i = int * (stores signed integer)                                   
    //      4 = uint32_t * (stores 32-bit unsigned integer)                     
    //      8 = uint64_t * (stores 64-bit unsigned integer)                     
    //      s = char ** (allocates new string)                                  
    //      b = byte **, size_t * (2 arguments) (allocates memory)              
    //      c = zchunk_t ** (creates zchunk)                                    
    //      f = zframe_t ** (creates zframe)                                    
    //      U = zuuid_t * (creates a zuuid with the data)                       
    //      h = zhashx_t ** (creates zhashx)                                    
    //      p = void ** (stores pointer)                                        
    //      m = zmsg_t ** (creates a zmsg with the remaing frames)              
    //      z = null, asserts empty frame (0 arguments)                         
    //      u = uint * (stores unsigned integer, deprecated)                    
    //                                                                          
    //  Note that zsock_recv creates the returned objects, and the caller must  
    //  destroy them when finished with them. The supplied pointers do not need 
    //  to be initialized. Returns 0 if successful, or -1 if it failed to recv  
    //  a message, in which case the pointers are not modified. When message    
    //  frames are truncated (a short message), sets return values to zero/null.
    //  If an argument pointer is NULL, does not store any value (skips it).    
    //  An 'n' picture matches an empty frame; if the message does not match,   
    //  the method will return -1.                                              
    int recv (const QString &picture,  ...);

    //  Receive a 'picture' message from the socket (or actor). This is a    
    //  va_list version of zsock_recv (), so please consult its documentation
    //  for the details.                                                     
    int vrecv (const QString &picture, va_list argptr);

    //  Return socket routing ID if any. This returns 0 if the socket is not
    //  of type ZMQ_SERVER or if no request was already received on it.     
    quint32 routingId ();

    //  Set routing ID on socket. The socket MUST be of type ZMQ_SERVER.        
    //  This will be used when sending messages on the socket via the zsock API.
    void setRoutingId (quint32 routingId);

    //  Set socket to use unbounded pipes (HWM=0); use this in cases when you are
    //  totally certain the message volume can fit in memory. This method works  
    //  across all versions of ZeroMQ. Takes a polymorphic socket reference.     
    void setUnbounded ();

    //  Send a signal over a socket. A signal is a short message carrying a   
    //  success/failure code (by convention, 0 means OK). Signals are encoded 
    //  to be distinguishable from "normal" messages. Accepts a zsock_t or a  
    //  zactor_t argument, and returns 0 if successful, -1 if the signal could
    //  not be sent. Takes a polymorphic socket reference.                    
    int signal (byte status);

    //  Wait on a signal. Use this to coordinate between threads, over pipe  
    //  pairs. Blocks until the signal is received. Returns -1 on error, 0 or
    //  greater on success. Accepts a zsock_t or a zactor_t as argument.     
    //  Takes a polymorphic socket reference.                                
    int wait ();

    //  If there is a partial message still waiting on the socket, remove and    
    //  discard it. This is useful when reading partial messages, to get specific
    //  message types.                                                           
    void flush ();

    //  Join a group for the RADIO-DISH pattern. Call only on ZMQ_DISH.
    //  Returns 0 if OK, -1 if failed.                                 
    int join (const QString &group);

    //  Leave a group for the RADIO-DISH pattern. Call only on ZMQ_DISH.
    //  Returns 0 if OK, -1 if failed.                                  
    int leave (const QString &group);

    //  Probe the supplied object, and report if it looks like a zsock_t.
    //  Takes a polymorphic socket reference.                            
    static bool is (void *self);

    //  Probe the supplied reference. If it looks like a zsock_t instance, return
    //  the underlying libzmq socket handle; else if it looks like a file        
    //  descriptor, return NULL; else if it looks like a libzmq socket handle,   
    //  return the supplied value. Takes a polymorphic socket reference.         
    static void * resolve (void *self);

    //  Get socket option `heartbeat_ivl`.
    //  Available from libzmq 4.2.0.      
    int heartbeatIvl ();

    //  Set socket option `heartbeat_ivl`.
    //  Available from libzmq 4.2.0.      
    void setHeartbeatIvl (int heartbeatIvl);

    //  Get socket option `heartbeat_ttl`.
    //  Available from libzmq 4.2.0.      
    int heartbeatTtl ();

    //  Set socket option `heartbeat_ttl`.
    //  Available from libzmq 4.2.0.      
    void setHeartbeatTtl (int heartbeatTtl);

    //  Get socket option `heartbeat_timeout`.
    //  Available from libzmq 4.2.0.          
    int heartbeatTimeout ();

    //  Set socket option `heartbeat_timeout`.
    //  Available from libzmq 4.2.0.          
    void setHeartbeatTimeout (int heartbeatTimeout);

    //  Get socket option `use_fd`. 
    //  Available from libzmq 4.2.0.
    int useFd ();

    //  Set socket option `use_fd`. 
    //  Available from libzmq 4.2.0.
    void setUseFd (int useFd);

    //  Set socket option `xpub_manual`.
    //  Available from libzmq 4.2.0.    
    void setXpubManual (int xpubManual);

    //  Set socket option `xpub_welcome_msg`.
    //  Available from libzmq 4.2.0.         
    void setXpubWelcomeMsg (const QString &xpubWelcomeMsg);

    //  Set socket option `stream_notify`.
    //  Available from libzmq 4.2.0.      
    void setStreamNotify (int streamNotify);

    //  Get socket option `invert_matching`.
    //  Available from libzmq 4.2.0.        
    int invertMatching ();

    //  Set socket option `invert_matching`.
    //  Available from libzmq 4.2.0.        
    void setInvertMatching (int invertMatching);

    //  Set socket option `xpub_verboser`.
    //  Available from libzmq 4.2.0.      
    void setXpubVerboser (int xpubVerboser);

    //  Get socket option `connect_timeout`.
    //  Available from libzmq 4.2.0.        
    int connectTimeout ();

    //  Set socket option `connect_timeout`.
    //  Available from libzmq 4.2.0.        
    void setConnectTimeout (int connectTimeout);

    //  Get socket option `tcp_maxrt`.
    //  Available from libzmq 4.2.0.  
    int tcpMaxrt ();

    //  Set socket option `tcp_maxrt`.
    //  Available from libzmq 4.2.0.  
    void setTcpMaxrt (int tcpMaxrt);

    //  Get socket option `thread_safe`.
    //  Available from libzmq 4.2.0.    
    int threadSafe ();

    //  Get socket option `multicast_maxtpdu`.
    //  Available from libzmq 4.2.0.          
    int multicastMaxtpdu ();

    //  Set socket option `multicast_maxtpdu`.
    //  Available from libzmq 4.2.0.          
    void setMulticastMaxtpdu (int multicastMaxtpdu);

    //  Get socket option `vmci_buffer_size`.
    //  Available from libzmq 4.2.0.         
    int vmciBufferSize ();

    //  Set socket option `vmci_buffer_size`.
    //  Available from libzmq 4.2.0.         
    void setVmciBufferSize (int vmciBufferSize);

    //  Get socket option `vmci_buffer_min_size`.
    //  Available from libzmq 4.2.0.             
    int vmciBufferMinSize ();

    //  Set socket option `vmci_buffer_min_size`.
    //  Available from libzmq 4.2.0.             
    void setVmciBufferMinSize (int vmciBufferMinSize);

    //  Get socket option `vmci_buffer_max_size`.
    //  Available from libzmq 4.2.0.             
    int vmciBufferMaxSize ();

    //  Set socket option `vmci_buffer_max_size`.
    //  Available from libzmq 4.2.0.             
    void setVmciBufferMaxSize (int vmciBufferMaxSize);

    //  Get socket option `vmci_connect_timeout`.
    //  Available from libzmq 4.2.0.             
    int vmciConnectTimeout ();

    //  Set socket option `vmci_connect_timeout`.
    //  Available from libzmq 4.2.0.             
    void setVmciConnectTimeout (int vmciConnectTimeout);

    //  Get socket option `tos`.    
    //  Available from libzmq 4.1.0.
    int tos ();

    //  Set socket option `tos`.    
    //  Available from libzmq 4.1.0.
    void setTos (int tos);

    //  Set socket option `router_handover`.
    //  Available from libzmq 4.1.0.        
    void setRouterHandover (int routerHandover);

    //  Set socket option `connect_rid`.
    //  Available from libzmq 4.1.0.    
    void setConnectRid (const QString &connectRid);

    //  Set socket option `connect_rid` from 32-octet binary
    //  Available from libzmq 4.1.0.                        
    void setConnectRidBin (const byte *connectRid);

    //  Get socket option `handshake_ivl`.
    //  Available from libzmq 4.1.0.      
    int handshakeIvl ();

    //  Set socket option `handshake_ivl`.
    //  Available from libzmq 4.1.0.      
    void setHandshakeIvl (int handshakeIvl);

    //  Get socket option `socks_proxy`.
    //  Available from libzmq 4.1.0.    
    QString socksProxy ();

    //  Set socket option `socks_proxy`.
    //  Available from libzmq 4.1.0.    
    void setSocksProxy (const QString &socksProxy);

    //  Set socket option `xpub_nodrop`.
    //  Available from libzmq 4.1.0.    
    void setXpubNodrop (int xpubNodrop);

    //  Set socket option `router_mandatory`.
    //  Available from libzmq 4.0.0.         
    void setRouterMandatory (int routerMandatory);

    //  Set socket option `probe_router`.
    //  Available from libzmq 4.0.0.     
    void setProbeRouter (int probeRouter);

    //  Set socket option `req_relaxed`.
    //  Available from libzmq 4.0.0.    
    void setReqRelaxed (int reqRelaxed);

    //  Set socket option `req_correlate`.
    //  Available from libzmq 4.0.0.      
    void setReqCorrelate (int reqCorrelate);

    //  Set socket option `conflate`.
    //  Available from libzmq 4.0.0. 
    void setConflate (int conflate);

    //  Get socket option `zap_domain`.
    //  Available from libzmq 4.0.0.   
    QString zapDomain ();

    //  Set socket option `zap_domain`.
    //  Available from libzmq 4.0.0.   
    void setZapDomain (const QString &zapDomain);

    //  Get socket option `mechanism`.
    //  Available from libzmq 4.0.0.  
    int mechanism ();

    //  Get socket option `plain_server`.
    //  Available from libzmq 4.0.0.     
    int plainServer ();

    //  Set socket option `plain_server`.
    //  Available from libzmq 4.0.0.     
    void setPlainServer (int plainServer);

    //  Get socket option `plain_username`.
    //  Available from libzmq 4.0.0.       
    QString plainUsername ();

    //  Set socket option `plain_username`.
    //  Available from libzmq 4.0.0.       
    void setPlainUsername (const QString &plainUsername);

    //  Get socket option `plain_password`.
    //  Available from libzmq 4.0.0.       
    QString plainPassword ();

    //  Set socket option `plain_password`.
    //  Available from libzmq 4.0.0.       
    void setPlainPassword (const QString &plainPassword);

    //  Get socket option `curve_server`.
    //  Available from libzmq 4.0.0.     
    int curveServer ();

    //  Set socket option `curve_server`.
    //  Available from libzmq 4.0.0.     
    void setCurveServer (int curveServer);

    //  Get socket option `curve_publickey`.
    //  Available from libzmq 4.0.0.        
    QString curvePublickey ();

    //  Set socket option `curve_publickey`.
    //  Available from libzmq 4.0.0.        
    void setCurvePublickey (const QString &curvePublickey);

    //  Set socket option `curve_publickey` from 32-octet binary
    //  Available from libzmq 4.0.0.                            
    void setCurvePublickeyBin (const byte *curvePublickey);

    //  Get socket option `curve_secretkey`.
    //  Available from libzmq 4.0.0.        
    QString curveSecretkey ();

    //  Set socket option `curve_secretkey`.
    //  Available from libzmq 4.0.0.        
    void setCurveSecretkey (const QString &curveSecretkey);

    //  Set socket option `curve_secretkey` from 32-octet binary
    //  Available from libzmq 4.0.0.                            
    void setCurveSecretkeyBin (const byte *curveSecretkey);

    //  Get socket option `curve_serverkey`.
    //  Available from libzmq 4.0.0.        
    QString curveServerkey ();

    //  Set socket option `curve_serverkey`.
    //  Available from libzmq 4.0.0.        
    void setCurveServerkey (const QString &curveServerkey);

    //  Set socket option `curve_serverkey` from 32-octet binary
    //  Available from libzmq 4.0.0.                            
    void setCurveServerkeyBin (const byte *curveServerkey);

    //  Get socket option `gssapi_server`.
    //  Available from libzmq 4.0.0.      
    int gssapiServer ();

    //  Set socket option `gssapi_server`.
    //  Available from libzmq 4.0.0.      
    void setGssapiServer (int gssapiServer);

    //  Get socket option `gssapi_plaintext`.
    //  Available from libzmq 4.0.0.         
    int gssapiPlaintext ();

    //  Set socket option `gssapi_plaintext`.
    //  Available from libzmq 4.0.0.         
    void setGssapiPlaintext (int gssapiPlaintext);

    //  Get socket option `gssapi_principal`.
    //  Available from libzmq 4.0.0.         
    QString gssapiPrincipal ();

    //  Set socket option `gssapi_principal`.
    //  Available from libzmq 4.0.0.         
    void setGssapiPrincipal (const QString &gssapiPrincipal);

    //  Get socket option `gssapi_service_principal`.
    //  Available from libzmq 4.0.0.                 
    QString gssapiServicePrincipal ();

    //  Set socket option `gssapi_service_principal`.
    //  Available from libzmq 4.0.0.                 
    void setGssapiServicePrincipal (const QString &gssapiServicePrincipal);

    //  Get socket option `ipv6`.   
    //  Available from libzmq 4.0.0.
    int ipv6 ();

    //  Set socket option `ipv6`.   
    //  Available from libzmq 4.0.0.
    void setIpv6 (int ipv6);

    //  Get socket option `immediate`.
    //  Available from libzmq 4.0.0.  
    int immediate ();

    //  Set socket option `immediate`.
    //  Available from libzmq 4.0.0.  
    void setImmediate (int immediate);

    //  Get socket option `type`.   
    //  Available from libzmq 3.0.0.
    int type ();

    //  Get socket option `sndhwm`. 
    //  Available from libzmq 3.0.0.
    int sndhwm ();

    //  Set socket option `sndhwm`. 
    //  Available from libzmq 3.0.0.
    void setSndhwm (int sndhwm);

    //  Get socket option `rcvhwm`. 
    //  Available from libzmq 3.0.0.
    int rcvhwm ();

    //  Set socket option `rcvhwm`. 
    //  Available from libzmq 3.0.0.
    void setRcvhwm (int rcvhwm);

    //  Get socket option `affinity`.
    //  Available from libzmq 3.0.0. 
    int affinity ();

    //  Set socket option `affinity`.
    //  Available from libzmq 3.0.0. 
    void setAffinity (int affinity);

    //  Set socket option `subscribe`.
    //  Available from libzmq 3.0.0.  
    void setSubscribe (const QString &subscribe);

    //  Set socket option `unsubscribe`.
    //  Available from libzmq 3.0.0.    
    void setUnsubscribe (const QString &unsubscribe);

    //  Get socket option `identity`.
    //  Available from libzmq 3.0.0. 
    QString identity ();

    //  Set socket option `identity`.
    //  Available from libzmq 3.0.0. 
    void setIdentity (const QString &identity);

    //  Get socket option `rate`.   
    //  Available from libzmq 3.0.0.
    int rate ();

    //  Set socket option `rate`.   
    //  Available from libzmq 3.0.0.
    void setRate (int rate);

    //  Get socket option `recovery_ivl`.
    //  Available from libzmq 3.0.0.     
    int recoveryIvl ();

    //  Set socket option `recovery_ivl`.
    //  Available from libzmq 3.0.0.     
    void setRecoveryIvl (int recoveryIvl);

    //  Get socket option `sndbuf`. 
    //  Available from libzmq 3.0.0.
    int sndbuf ();

    //  Set socket option `sndbuf`. 
    //  Available from libzmq 3.0.0.
    void setSndbuf (int sndbuf);

    //  Get socket option `rcvbuf`. 
    //  Available from libzmq 3.0.0.
    int rcvbuf ();

    //  Set socket option `rcvbuf`. 
    //  Available from libzmq 3.0.0.
    void setRcvbuf (int rcvbuf);

    //  Get socket option `linger`. 
    //  Available from libzmq 3.0.0.
    int linger ();

    //  Set socket option `linger`. 
    //  Available from libzmq 3.0.0.
    void setLinger (int linger);

    //  Get socket option `reconnect_ivl`.
    //  Available from libzmq 3.0.0.      
    int reconnectIvl ();

    //  Set socket option `reconnect_ivl`.
    //  Available from libzmq 3.0.0.      
    void setReconnectIvl (int reconnectIvl);

    //  Get socket option `reconnect_ivl_max`.
    //  Available from libzmq 3.0.0.          
    int reconnectIvlMax ();

    //  Set socket option `reconnect_ivl_max`.
    //  Available from libzmq 3.0.0.          
    void setReconnectIvlMax (int reconnectIvlMax);

    //  Get socket option `backlog`.
    //  Available from libzmq 3.0.0.
    int backlog ();

    //  Set socket option `backlog`.
    //  Available from libzmq 3.0.0.
    void setBacklog (int backlog);

    //  Get socket option `maxmsgsize`.
    //  Available from libzmq 3.0.0.   
    int maxmsgsize ();

    //  Set socket option `maxmsgsize`.
    //  Available from libzmq 3.0.0.   
    void setMaxmsgsize (int maxmsgsize);

    //  Get socket option `multicast_hops`.
    //  Available from libzmq 3.0.0.       
    int multicastHops ();

    //  Set socket option `multicast_hops`.
    //  Available from libzmq 3.0.0.       
    void setMulticastHops (int multicastHops);

    //  Get socket option `rcvtimeo`.
    //  Available from libzmq 3.0.0. 
    int rcvtimeo ();

    //  Set socket option `rcvtimeo`.
    //  Available from libzmq 3.0.0. 
    void setRcvtimeo (int rcvtimeo);

    //  Get socket option `sndtimeo`.
    //  Available from libzmq 3.0.0. 
    int sndtimeo ();

    //  Set socket option `sndtimeo`.
    //  Available from libzmq 3.0.0. 
    void setSndtimeo (int sndtimeo);

    //  Set socket option `xpub_verbose`.
    //  Available from libzmq 3.0.0.     
    void setXpubVerbose (int xpubVerbose);

    //  Get socket option `tcp_keepalive`.
    //  Available from libzmq 3.0.0.      
    int tcpKeepalive ();

    //  Set socket option `tcp_keepalive`.
    //  Available from libzmq 3.0.0.      
    void setTcpKeepalive (int tcpKeepalive);

    //  Get socket option `tcp_keepalive_idle`.
    //  Available from libzmq 3.0.0.           
    int tcpKeepaliveIdle ();

    //  Set socket option `tcp_keepalive_idle`.
    //  Available from libzmq 3.0.0.           
    void setTcpKeepaliveIdle (int tcpKeepaliveIdle);

    //  Get socket option `tcp_keepalive_cnt`.
    //  Available from libzmq 3.0.0.          
    int tcpKeepaliveCnt ();

    //  Set socket option `tcp_keepalive_cnt`.
    //  Available from libzmq 3.0.0.          
    void setTcpKeepaliveCnt (int tcpKeepaliveCnt);

    //  Get socket option `tcp_keepalive_intvl`.
    //  Available from libzmq 3.0.0.            
    int tcpKeepaliveIntvl ();

    //  Set socket option `tcp_keepalive_intvl`.
    //  Available from libzmq 3.0.0.            
    void setTcpKeepaliveIntvl (int tcpKeepaliveIntvl);

    //  Get socket option `tcp_accept_filter`.
    //  Available from libzmq 3.0.0.          
    QString tcpAcceptFilter ();

    //  Set socket option `tcp_accept_filter`.
    //  Available from libzmq 3.0.0.          
    void setTcpAcceptFilter (const QString &tcpAcceptFilter);

    //  Get socket option `rcvmore`.
    //  Available from libzmq 3.0.0.
    int rcvmore ();

    //  Get socket option `fd`.     
    //  Available from libzmq 3.0.0.
    SOCKET fd ();

    //  Get socket option `events`. 
    //  Available from libzmq 3.0.0.
    int events ();

    //  Get socket option `last_endpoint`.
    //  Available from libzmq 3.0.0.      
    QString lastEndpoint ();

    //  Set socket option `router_raw`.
    //  Available from libzmq 3.0.0.   
    void setRouterRaw (int routerRaw);

    //  Get socket option `ipv4only`.
    //  Available from libzmq 3.0.0. 
    int ipv4only ();

    //  Set socket option `ipv4only`.
    //  Available from libzmq 3.0.0. 
    void setIpv4only (int ipv4only);

    //  Set socket option `delay_attach_on_connect`.
    //  Available from libzmq 3.0.0.                
    void setDelayAttachOnConnect (int delayAttachOnConnect);

    //  Self test of this class.
    static void test (bool verbose);

    zsock_t *self;
};
#endif //  Q_ZSOCK_H
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/

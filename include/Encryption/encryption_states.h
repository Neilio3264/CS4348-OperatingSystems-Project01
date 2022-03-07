#ifndef KRYPTO_ENCRYPTION_STATES_H
#define KRYPTO_ENCRYPTION_STATES_H

namespace krypto
{
    enum encryption_states
    {
        IDLE,
        PASSKEY,
        ENCRYPT,
        DECRYPT,
        QUIT,
        RESULT,
        ERROR
    };
}

#endif
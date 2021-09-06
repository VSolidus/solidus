VSolidus Core integration/staging tree
=====================================

What is VSolidus?
----------------

VSolidus (Solidus) is the result of our joint efforts to develop a new, better and faster transactional coin that can serve as a good alternative to the current, industry standard Bitcoin. Various alternative currencies (alt coins) have come and gone. Some brought innovation, but they all had problems.

Solidus is a peer-to-peer internet currency that allows instant, nearly free payments to anyone, anywhere in the world. Solidus is a global payment network that is fully decentralized and has no central authorities. No one can counterfeit transactions, initiate chargebacks, or seize funds. Not even a government. While this makes it harder to retrieve lost money, it also makes it harder to lose your money. With enough care, this coin is a far more practical alternative to FIAT money.

Here at Solidus, we care about our community, we ensure your journey mining and transacting on our platform is a pleasant experience and there is always someone on hand to help.

We reward and incentivise community members with free Solidus to help grow the community and further enhance the Solidus offering.

License
-------

Solidus Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags] are created
regularly to indicate new official, stable release versions of Solidus Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md)
and useful hints for developers can be found in [doc/developer-notes.md](doc/developer-notes.md).

Developer IRC can be found on Freenode at #solidus-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Solidus periodically.

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

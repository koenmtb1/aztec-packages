// SPDX-License-Identifier: UNLICENSED
pragma solidity >=0.8.27;

import {Test} from "forge-std/Test.sol";
import {Gerousia} from "@aztec/governance/Gerousia.sol";
import {Errors} from "@aztec/governance/libraries/Errors.sol";
import {IRegistry} from "@aztec/governance/interfaces/IRegistry.sol";
import {IApella} from "@aztec/governance/interfaces/IApella.sol";

contract ConstructorTest is Test {
  IApella internal constant APELLA = IApella(address(0x01));
  IRegistry internal constant REGISTRY = IRegistry(address(0x02));

  function test_WhenNIsLessThanOrEqualHalfOfM(uint256 _n, uint256 _m) external {
    // it revert

    uint256 n = bound(_n, 0, _m / 2);

    vm.expectRevert(abi.encodeWithSelector(Errors.Gerousia__InvalidNAndMValues.selector, n, _m));
    new Gerousia(APELLA, REGISTRY, n, _m);
  }

  function test_WhenNLargerThanM(uint256 _n, uint256 _m) external {
    // it revert
    uint256 m = bound(_m, 0, type(uint256).max - 1);
    uint256 n = bound(_n, m + 1, type(uint256).max);

    vm.expectRevert(abi.encodeWithSelector(Errors.Gerousia__NCannotBeLargerTHanM.selector, n, m));
    new Gerousia(APELLA, REGISTRY, n, m);
  }

  function test_WhenNIsGreatherThanHalfOfM(uint256 _n, uint256 _m) external {
    // it deploys

    uint256 m = bound(_m, 1, type(uint256).max);
    uint256 n = bound(_n, m / 2 + 1, m);

    Gerousia g = new Gerousia(APELLA, REGISTRY, n, m);

    assertEq(address(g.APELLA()), address(APELLA));
    assertEq(address(g.REGISTRY()), address(REGISTRY));
    assertEq(g.N(), n);
    assertEq(g.M(), m);
  }
}

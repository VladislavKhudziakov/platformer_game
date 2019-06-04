//
//  BaseWeapon.hpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 6/5/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef BaseWeapon_hpp
#define BaseWeapon_hpp


namespace GO {
  template <typename Ammunition>
  class BaseWeapon
  {
    Ammunition ammo;
    
  public:
    BaseWeapon(const Ammunition&);
    void shootOnce();
  };
}


#endif /* BaseWeapon_hpp */

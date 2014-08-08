#include <autonomy/core.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class mock_actor : public autonomy::actor_base
{
  public:
    static mock_actor* global;
    mock_actor()
    {
      global = this;
    }
    void init() { }
    MOCK_METHOD0(test, void());
    MOCK_METHOD0(rettest, int());
    MOCK_METHOD1(argtest, void(int));


    AUTONOMY_ACTOR_HANDLERS(mock_actor, (init,test, rettest, argtest));
};
mock_actor* mock_actor::global = nullptr;

class fwd_actor : public autonomy::actor_base
{
  public:
    static fwd_actor* global;
    fwd_actor()
    {
      global = this;
    }
    fwd_actor(autonomy::actor mock)
      : mock_(mock) {}

    void test()
    {
      forward_to(mock_);
    }

    AUTONOMY_ACTOR_HANDLERS(fwd_actor, (test));
  private:
    autonomy::actor mock_;
};
fwd_actor* fwd_actor::global = nullptr;

using ::testing::Return;

TEST(ActorFeature, CanCreateAndSend)
{
  autonomy::actor_controller ac;
  autonomy::actor mock( ac.spawn<mock_actor>() );
  ac.send<ac.msg("init")>(mock).wait();
  ASSERT_NE(nullptr, mock_actor::global);
  EXPECT_CALL(*mock_actor::global,test()).Times(1);
  ac.send<ac.msg("test")>(mock);
}

TEST(ActorFeature, CanSendArguments)
{
  autonomy::actor_controller ac;
  autonomy::actor mock( ac.spawn<mock_actor>() );
  ac.send<ac.msg("init")>(mock).wait();
  ASSERT_NE(nullptr, mock_actor::global);
  EXPECT_CALL(*mock_actor::global,argtest(5)).Times(1);
  ac.send<ac.msg("argtest")>(mock,5);
}

TEST(ActorFeature, CanGetReturns)
{
  autonomy::actor_controller ac;
  autonomy::actor mock( ac.spawn<mock_actor>() );
  ac.send<ac.msg("init")>(mock).wait();
  ASSERT_NE(nullptr, mock_actor::global);
  EXPECT_CALL(*mock_actor::global,rettest()).Times(2).WillRepeatedly(Return(5));
  EXPECT_EQ(5,ac.send<ac.msg("rettest")>(mock).get<int>());
  int ret{0};
  ac.send<ac.msg("rettest")>(mock).then([&](int v){
    ret = v;
  }).wait();
  EXPECT_EQ(5,ret);
}

TEST(ActorFeature, CanUseGroups)
{
  autonomy::actor_controller ac;
  autonomy::actor mock( ac.spawn<mock_actor>() );
  autonomy::actor_group grp( ac.create_group() );
  grp.add(mock);
  ac.send<ac.msg("init")>(mock).wait();
  ASSERT_NE(nullptr, mock_actor::global);
  EXPECT_CALL(*mock_actor::global,test()).Times(1);
  ac.send<ac.msg("test")>(grp);
}

TEST(ActorFeature, CanForward)
{
  autonomy::actor_controller ac;
  autonomy::actor mock( ac.spawn<mock_actor>() );
  ac.send<ac.msg("init")>(mock).wait();
  ASSERT_NE(nullptr, mock_actor::global);
  EXPECT_CALL(*mock_actor::global,test()).Times(1);
  autonomy::actor fwd( ac.spawn<fwd_actor>(mock) );
  ac.send<ac.msg("test")>(fwd);
}

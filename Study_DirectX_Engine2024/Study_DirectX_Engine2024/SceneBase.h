#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <functional>


// オブジェクトプールの実装
// メモリ割り当てを最適化し、オブジェクトの再利用を可能にする
template<typename T>
class ObjectPool {
private:
    std::vector<std::unique_ptr<T>> objects;
    std::vector<T*> freeList;

public:
    // オブジェクトを取得する（新規作成または再利用）
    T* Acquire() {
        if (freeList.empty()) {
            objects.push_back(std::make_unique<T>());
            return objects.back().get();
        }
        T* obj = freeList.back();
        freeList.pop_back();
        return obj;
    }

    // オブジェクトを解放し、再利用可能にする
    void Release(T* obj) {
        freeList.push_back(obj);
    }
};

// シーンオブジェクトの基底クラス
class SceneObjectBase {
public:
    virtual ~SceneObjectBase() = default;
};

// 型安全なシーンオブジェクトのクラス
template<class T>
class SceneObject : public SceneObjectBase {
public:
    SceneObject(std::unique_ptr<T> ptr) : m_pObj(std::move(ptr)) {}
    T* Get() { return m_pObj.get(); }

private:
    std::unique_ptr<T> m_pObj;
};

/// <summary>
/// Scene基底クラス
/// </summary>
class SceneBase
{
private:

    // オブジェクトとその名前を格納するマップを作成しておく
    using Objects = std::unordered_map<std::string, std::unique_ptr<SceneObjectBase>>;
    using Items = std::vector<std::string>;


public:
    // コンストラクタとデストラクタ
    SceneBase() = default;
    virtual ~SceneBase() = default;
    // シーンの初期化処理
    virtual void Initialize() = 0;
    // シーンの更新処理
    virtual void Update(float _deltaTime) = 0;
    // シーンの描画処理
    virtual void Draw() = 0;
    // シーンの終了処理
    virtual void Finalize() = 0;
    // サブシーンの追加
    template<class T>
    T* AddSubScene();
    // サブシーンの削除
    void RemoveSubScene();

    // オブジェクトの生成
    template<class T>
    T* CreateObj(const char* name);
    // オブジェクトの破棄
    void DestroyObj(const char* name);
    // オブジェクトの取得
    template<class T>
    T* GetObj(const char* name);
private:
    static Objects m_objects;
    // オブジェクト生成用ファクトリー関数のマップ
    static std::unordered_map<std::string, std::function<std::unique_ptr<SceneObjectBase>()>> m_factories;

protected:
    SceneBase* m_pParent = nullptr;
    std::unique_ptr<SceneBase> m_pSubScene;
    Items m_items;

    // オブジェクト生成用ファクトリー関数の登録
    template<class T>
    static void RegisterFactory() {
        std::string typeName = typeid(T).name();
        m_factories[typeName] = []() { return std::make_unique<SceneObject<T>>(std::make_unique<T>()); };
    }
};

// サブシーンの追加
template<class T>
T* SceneBase::AddSubScene() {
    m_pSubScene = std::make_unique<T>();
    m_pSubScene->m_pParent = this;
    m_pSubScene->Initialize();
    return static_cast<T*>(m_pSubScene.get());
}

// オブジェクトの生成
template<class T>
T* SceneBase::CreateObj(const char* name) {
    std::string typeName = typeid(T).name();
    auto it = m_factories.find(typeName);
    if (it == m_factories.end()) {
        // ファクトリーが未登録の場合、登録する
        RegisterFactory<T>();
        it = m_factories.find(typeName);
    }

    // オブジェクトの生成と登録
    auto obj = it->second();
    auto* pObj = static_cast<SceneObject<T>*>(obj.get())->Get();
    m_objects[name] = std::move(obj);
    m_items.push_back(name);
    return pObj;
}

// オブジェクトの取得
template<class T>
T* SceneBase::GetObj(const char* name) {
    auto it = m_objects.find(name);
    if (it == m_objects.end()) return nullptr;
    return static_cast<SceneObject<T>*>(it->second.get())->Get();
}

